#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>
#include <time.h>
#include "barycentre.h"
#include "serial.h"
#include "couleur.h"
#include <stdbool.h>
#include <math.h>

//t exec = 0.3531 s
using namespace cv;
using namespace std;

#define IMG_HEIGHT 320
#define IMG_WIDTH 240
#define IMG_FLIP 1

#define IMAGE 1
#define DEBUG_SIMPLIFY 1
#define DEBUG_ONLY_OBJECT 0
#define ZONES 0
#define RECORD 0

int main(int, char**)
{   
  Vec3f pixel;

    VideoCapture cap(1); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat frame;

    #if IMAGE == 1
    namedWindow("MyCam",1);
    #endif
  
  
    cap.set(CV_CAP_PROP_FRAME_WIDTH,IMG_WIDTH);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,IMG_HEIGHT);


MatIterator_<Vec3b> it, end;
int index_pix = 0;
ListePoints lp = initListePoint(IMG_HEIGHT*IMG_WIDTH);
B_Point p;
Couleur couleur = createCouleur(0,0,0);
serial_com sc = newSerial_Com();
serial_open(&sc);

#if RECORD == 1
FILE * fileNorme = fopen("../rapport/result.txt","w");
FILE * fileX = fopen("../rapport/errx.txt","w");
FILE * fileY = fopen("../rapport/erry.txt","w");
double time_taken;
clock_t t1 = clock();
#endif
    while(1
        #if RECORD == 1
        time_taken < 10
        #endif
    ){
           if(cap.read(frame)){// get a new frame from camera

                #if IMG_FLIP == 1
                    //Rotate image 90° anti-clockwise
                    transpose(frame,frame);
                    flip(frame,frame,-1);
                #endif

            index_pix = 0;
            lp.size = 0;
            for( it = frame.begin<Vec3b>(), end = frame.end<Vec3b>(); it != end; ++it){
                couleur.r = (*it)[0];
                couleur.g = (*it)[1];
                couleur.b = (*it)[2];

                int x = index_pix / IMG_WIDTH;
                int y = index_pix % IMG_WIDTH;

                if(estRouge(couleur)){
                    #if DEBUG_ONLY_OBJECT == 0 && IMAGE == 1
                    
                        (*it)[0]=0;
                        (*it)[1]=0;
                        (*it)[2]=0;

                    #else
                        #if IMAGE == 1

                        (*it)[0]=255;
                        (*it)[1]=255;
                        (*it)[2]=255;

                        #endif
                    #endif
                    
                    p = initPoint(x,y);
                    inserPoint(&lp, p);
                }

                #if (DEBUG_SIMPLIFY == 1 || DEBUG_ONLY_OBJECT == 1) && IMAGE == 1

                    else{
                        (*it)[0]=255;
                        (*it)[1]=255;
                        (*it)[2]=255;
                    }

                #endif

                index_pix++;
            }

            B_Point barycentre = calculateBarycentre(lp);
            barycentre = convertToCenter(barycentre,IMG_HEIGHT,IMG_WIDTH);
            if(lp.size > 0){
                const char * com = getCommandeX(barycentre);
                serial_write(sc,com);
                com = getCommandeY(barycentre);
                serial_write(sc,com);   
            }
            #if RECORD == 1
            time_taken = ((double)clock()-t1)/CLOCKS_PER_SEC;
            fprintf(fileNorme,"%lf %d\n",time_taken,(int)sqrt((barycentre.x*barycentre.x)+(barycentre.y*barycentre.y)));
            fprintf(fileX,"%lf %d\n",time_taken,barycentre.x);
            fprintf(fileY,"%lf %d\n",time_taken,barycentre.y);
            #endif
            
            #if DEBUG_ONLY_OBJECT == 1 && IMAGE == 1
                frame.at<Vec3b>(Point(barycentre.y,barycentre.x)) = {0,0,0};
                frame.at<Vec3b>(Point(barycentre.y+1,barycentre.x+1)) = {0,0,0};
                frame.at<Vec3b>(Point(barycentre.y+1,barycentre.x-1)) = {0,0,0};
                frame.at<Vec3b>(Point(barycentre.y-1,barycentre.x+1)) = {0,0,0};
                frame.at<Vec3b>(Point(barycentre.y-1,barycentre.x-1)) = {0,0,0};
            #endif
        
        #if IMAGE == 1
	     imshow("MyCam", frame);
        #endif

        }
        
        if(waitKey(5) >= 0) break;
   }
    // the camera will be deinitialized automatically in VideoCapture destructor 
    return 0;
}