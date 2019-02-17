// barcode reader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
const string name="Open_CV";
void paintRect(Mat I,uchar vl)
{
    // accept only char type matrices
    CV_Assert(I.depth() != sizeof(uchar));

    const int channels = I.channels();
    switch(channels)
    {
    case 1:
        {
            MatIterator_<uchar> it, end;
            for( it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
                *it = vl;
            break;
        }
    case 3:
        {
            MatIterator_<Vec3b> it, end;
            for( it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
            {
                (*it)[0] = vl;
                (*it)[1] = vl;
                (*it)[2] = vl;
            }
        }
    }

}
void readBarcode(Mat img)
{
	      ImageScanner scanner;  
      scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);   
      Mat imgout;  
      cvtColor(img,imgout,CV_GRAY2RGB);  
      int width = img.cols;  
      int height = img.rows;  
   uchar *raw = (uchar *)img.data;  
   // wrap image data  
   Image image(width, height, "Y800", raw, width * height);  
   // scan the image for barcodes  
   int n = scanner.scan(image);  
   // extract results  
   for(Image::SymbolIterator symbol = image.symbol_begin();  
     symbol != image.symbol_end();  
     ++symbol) {  
                vector<Point> vp;  
     // do something useful with results  
     cout << "decoded " << symbol->get_type_name()  
        << " symbol \"" << symbol->get_data() << '"' <<" "<< endl;  
           int n = symbol->get_location_size();  
           for(int i=0;i<n;i++){  
                vp.push_back(Point(symbol->get_location_x(i),symbol->get_location_y(i))); 
           }  
           RotatedRect r = minAreaRect(vp);  
           Point2f pts[4];  
           r.points(pts);  
           for(int i=0;i<4;i++){  
                line(imgout,pts[i],pts[(i+1)%4],Scalar(255,0,0),3);  
           }  
           cout<<"Angle: "<<r.angle<<endl;  
   }  
//    imshow(name,imgout);  
   // clean up  
   image.set_data(NULL, 0);  
}
void main()
{
	string s;
	int x,y,camid;

	cout<<"what cam will you chose :";
	cin>>camid;

	VideoCapture cam(camid);

	if(cam.isOpened()!=true){cout<<"Error get Cam"<<endl;return;}
	else cout<<"Ok"<<endl;
	namedWindow(name,WINDOW_AUTOSIZE);


	Mat Frame,Gray;
	while(1){
		cam.read(Frame);
		cvtColor(Frame,Gray,CV_BGR2GRAY,0);

		x= (int)Gray.cols / 2;
		y= 0;
					
		Mat buff (Gray, Rect(x,y,widthzone,Gray.rows));
		Mat buff2=buff.clone();
		readBarcode(buff2);
		paintRect(buff,0);
		imshow(name,Gray);
		waitKey(10);
	}
}