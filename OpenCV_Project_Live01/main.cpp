#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	CascadeClassifier face_cascade, eye_cascade;
	face_cascade.load("haarcascade_frontalface_default.xml");
	eye_cascade.load("haarcascade_eye.xml");

	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "Could not open camera" << endl;
		return -1;
	}

	Mat frame;
	while (true)
	{
		cap >> frame;
		vector<Rect> faces;
		face_cascade.detectMultiScale(frame, faces, 1.1, 4, 0, Size(30, 30));

		for (size_t i = 0; i < faces.size(); i++)
		{
			// �� ǥ��
			rectangle(frame, faces[i], Scalar(255, 0, 0), 2);

			//�� ���ο��� �� ����
			Mat faceROI = frame(faces[i]); // �� ������ ROI(Region of Interest)
			vector<Rect> eyes;
			eye_cascade.detectMultiScale(faceROI, eyes, 1.1, 4, 0, Size(15, 15));

			for (size_t j = 0; j < eyes.size(); j++)
			{
				Rect eyeRect = eyes[j];
				// ROI ������ �� ��ǥ�� ��ü ������ ��ǥ�� ��ȯ
				eyeRect.x += faces[i].x;
				eyeRect.y += faces[i].y;
				rectangle(frame, eyeRect, Scalar(0, 0, 255), 2);
			}
		}

		imshow("Face Detection", frame);
		
		char key = waitKey(10);

		if (key == 'p')
		{
			while (true) {
				char pauseKey = waitKey(10);
				if (pauseKey == 'p' || pauseKey == 27) { // p �Ǵ� ESC�� ���/����
					if (pauseKey == 27) return 0; // ESC�� ����
					break;
				}
			}
		}

		if (key == 27) { // 27 = ESC
			break;
		}

	}
	return 0;
}