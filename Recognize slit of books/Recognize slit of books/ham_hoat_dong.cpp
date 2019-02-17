VideoCapture FindConnectedCamera()
{
		VideoCapture buff(CAM_ID);
		if(buff.isOpened()!=true){cout<<"Error get Cam"<<endl;return NULL;}
		return buff;
}
