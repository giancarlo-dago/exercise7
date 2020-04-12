#include "ros/ros.h"
#include <tf/transform_listener.h>

void function (const std::string &target_frame, const std::string &source_frame, const ros::Time &time, const ros::Duration &timeout, tf::StampedTransform &transform, tf::TransformListener &listener, double roll, double pitch, double yaw, int i) {
	if( listener.waitForTransform(target_frame, source_frame, time, timeout) ) {
		listener.lookupTransform(target_frame, source_frame,  time, transform);
		std::cout << "[JOINT " << i << "]"<< std::endl << "Translation: [" << transform.getOrigin().x() << " " << transform.getOrigin().y() << " " << transform.getOrigin().z() << "]" << std::endl; 
		std::cout << "Rotation (quaternion): [" << transform.getRotation().w() << " " << transform.getRotation().x() << " " << transform.getRotation().y() << " " << transform.getRotation().z() << "]" << std::endl; 
		tf::Matrix3x3 m( transform.getRotation() );
		m.getRPY(roll, pitch, yaw);
		std::cout << "Rotation (in RPY): [" << roll << ", " << pitch << ", " << yaw << "]" << std::endl;
	} else { ROS_WARN("Transform not ready"); }
}


int main( int argc, char** argv ) {

	ros::init(argc, argv, "kukaiiwa_tf_publisher");
	ros::NodeHandle nh;
	sleep(1); 														//Wait ROS node starts
  	tf::TransformListener listener;									//Declare the listener to use c++ tf API
  	tf::StampedTransform transform;									//Declare the tranfsorm object to store tf data
  	double roll, pitch, yaw;

	for( int i=0; i<10; i++ ) {
		try {
			function ("/LBR_iiwa_7_R800_link2", "/LBR_iiwa_7_R800_link1", ros::Time::now(), ros::Duration(1.0), transform, listener, roll, pitch, yaw, 1);
			function ("/LBR_iiwa_7_R800_link3", "/LBR_iiwa_7_R800_link2", ros::Time::now(), ros::Duration(1.0), transform, listener, roll, pitch, yaw, 2);
			function ("/LBR_iiwa_7_R800_link4", "/LBR_iiwa_7_R800_link3", ros::Time::now(), ros::Duration(1.0), transform, listener, roll, pitch, yaw, 3);
			function ("/LBR_iiwa_7_R800_link5", "/LBR_iiwa_7_R800_link4", ros::Time::now(), ros::Duration(1.0), transform, listener, roll, pitch, yaw, 4);
			function ("/LBR_iiwa_7_R800_link6", "/LBR_iiwa_7_R800_link5", ros::Time::now(), ros::Duration(1.0), transform, listener, roll, pitch, yaw, 5);
			function ("/LBR_iiwa_7_R800_link7", "/LBR_iiwa_7_R800_link6", ros::Time::now(), ros::Duration(1.0), transform, listener, roll, pitch, yaw, 6);
			function ("/LBR_iiwa_7_R800_link8", "/LBR_iiwa_7_R800_link7", ros::Time::now(), ros::Duration(1.0), transform, listener, roll, pitch, yaw, 7);
			std::cout << "------------------------------------------------" << std::endl;
		}
		catch (tf::TransformException ex){
			ROS_ERROR("%s",ex.what());
			ros::Duration(1.0).sleep();
		}
		ros::Duration(1.0).sleep();	
	}
}
