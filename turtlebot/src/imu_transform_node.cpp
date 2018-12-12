#include <ros/ros.h>
#include <sensor_msgs/Imu.h>

ros::Publisher imuPub;

void imu_callback(const sensor_msgs::ImuConstPtr &imu_in)
{
	sensor_msgs::Imu imu_out = *imu_in;

	imu_out.orientation.x = imu_in->orientation.y;
	imu_out.orientation.y = -imu_in->orientation.x;
	imu_out.orientation.z = imu_in->orientation.z;

	imu_out.angular_velocity.x = imu_in->angular_velocity.y;
	imu_out.angular_velocity.y = -imu_in->angular_velocity.x;
	imu_out.angular_velocity.z = imu_in->angular_velocity.z;

	imu_out.linear_acceleration.x = imu_in->linear_acceleration.y;
	imu_out.linear_acceleration.y = -imu_in->linear_acceleration.x;
	imu_out.linear_acceleration.z = imu_in->linear_acceleration.z;

	imuPub.publish(imu_out);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "imu_transform_node");
    ros::NodeHandle n;
	
	imuPub = n.advertise<sensor_msgs::Imu>("output", 1, true);
	ros::Subscriber imuSub = n.subscribe("input", 10, &imu_callback);

	ros::spin();
	return 0;
}
