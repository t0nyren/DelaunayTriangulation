#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
using namespace std;
using namespace cv;

#define numLandmarks 83

static void draw_subdiv( Mat& img, Subdiv2D& subdiv, Scalar delaunay_color )
{
    vector<Vec6f> triangleList;
    subdiv.getTriangleList(triangleList);
    vector<Point> pt(3);

    for( size_t i = 0; i < triangleList.size(); i++ )
    {
        Vec6f t = triangleList[i];
        pt[0] = Point(cvRound(t[0]), cvRound(t[1]));
        pt[1] = Point(cvRound(t[2]), cvRound(t[3]));
        pt[2] = Point(cvRound(t[4]), cvRound(t[5]));
		bool draw=true;
		for(int i=0;i<3;i++){
		 if(pt[i].x>img.cols||pt[i].y>img.rows||pt[i].x<0||pt[i].y<0)
			draw=false;
		}
		if (draw){
			line(img, pt[0], pt[1], delaunay_color, 1);
			line(img, pt[1], pt[2], delaunay_color, 1);
			line(img, pt[2], pt[0], delaunay_color, 1);
		}
    }
}

int main(){
	Scalar active_facet_color(0, 0, 255), delaunay_color(255,255,255);
	ifstream finSrc;
	//read in dst img
	Mat src = imread("1.jpg", 1);
	Rect rect(0, 0, src.cols, src.rows);
    Subdiv2D subdiv(rect);	
	
	//parse landmarks of the two imgs
	finSrc.open("landmarks1.txt");
	if (finSrc.fail()){
		cout<<"Couldn't open landmarks files"<<endl;
	}
	Point* srcPoints = new Point[numLandmarks];
	
	//Delaunay Triangulation
	for (int i = 0; i < numLandmarks; i++){
		float x,y;
		finSrc>>x;
		finSrc>>y;
		srcPoints[i] = Point( cvRound(x/100*src.cols),cvRound(y/100*src.rows) );
		subdiv.insert(srcPoints[i]);
	}
	draw_subdiv( src, subdiv, delaunay_color );
	imwrite("dt.jpg", src);
	return 0;
}