#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <ras_arduino_msgs/ADConverter.h>
#include <geometry_msgs/PointStamped.h>
#include <transforms/IrTransformMsg.h>

class IrTransform {

public:
    tf::TransformListener listener;
    ros::NodeHandle node;
    ros::Subscriber ir_sub;
    ros::Publisher ir_pub;

    IrTransform() {
        node = ros::NodeHandle();
        ir_sub = node.subscribe("/ir_sensor_cm", 1, &IrTransform::IrCallback, this);
        ir_pub = node.advertise<transforms::IrTransformMsg>("/transformed_ir_points", 1);
    }
    ~IrTransform() {}


    void IrCallback(const ras_arduino_msgs::ADConverterConstPtr &msg) {

        geometry_msgs::PointStamped sensor1, sensor2, sensor3, sensor4;
        transforms::IrTransformMsg itmsg;

        try{
            geometry_msgs::PointStamped base_point1, base_point2, base_point3, base_point4;
            if (msg->ch1 < 30 && msg->ch1 > 0) {
                sensor1.header.frame_id = "sensor1";
                sensor1.point.y = msg->ch1/100;
                listener.waitForTransform("/sensor1", "/map", ros::Time::now(), ros::Duration(1));
                listener.transformPoint("map", sensor1, base_point1);
                itmsg.s1 = true;
                itmsg.p1 = base_point1;
            } else {
                itmsg.s1 = false;
            }
            if (msg->ch2 < 30 && msg->ch2 > 0) {
                sensor2.header.frame_id = "sensor2";
                sensor2.point.y = msg->ch2/100;
                listener.waitForTransform("/sensor2", "/map", ros::Time::now(), ros::Duration(1));
                listener.transformPoint("map", sensor2, base_point2);
                itmsg.s2 = true;
                itmsg.p2 = base_point2;
            } else {
                itmsg.s2 = false;
            }
            if (msg->ch3 < 30 && msg->ch3 > 0) {
                sensor3.header.frame_id = "sensor3";
                sensor3.point.y = msg->ch3/100;
                listener.waitForTransform("/sensor3", "/map", ros::Time::now(), ros::Duration(1));
                listener.transformPoint("map", sensor3, base_point3);
                itmsg.s3 = true;
                itmsg.p3 = base_point3;
            } else {
                itmsg.s3 = false;
            }
            if (msg->ch4 < 30 && msg->ch4 > 0) {
                sensor4.header.frame_id = "sensor4";
                sensor4.point.y = msg->ch4/100;
                listener.waitForTransform("/sensor4", "/map", ros::Time::now(), ros::Duration(1));
                listener.transformPoint("map", sensor4, base_point4);
                itmsg.s4 = true;
                itmsg.p4 = base_point4;
            } else {
                itmsg.s4 = false;
            }

            ir_pub.publish(itmsg);
/*
            ROS_INFO("sensor1: (%.2f, %.2f. %.2f) -----> map: (%.2f, %.2f, %.2f) at time %.2f",
                sensor1.point.x, sensor1.point.y, sensor1.point.z,
                base_point1.point.x, base_point1.point.y, base_point1.point.z, base_point1.header.stamp.toSec());
            ROS_INFO("sensor2: (%.2f, %.2f. %.2f) -----> map: (%.2f, %.2f, %.2f) at time %.2f",
                sensor2.point.x, sensor2.point.y, sensor2.point.z,
                base_point2.point.x, base_point2.point.y, base_point2.point.z, base_point2.header.stamp.toSec());
            ROS_INFO("sensor3: (%.2f, %.2f. %.2f) -----> map: (%.2f, %.2f, %.2f) at time %.2f",
                sensor3.point.x, sensor3.point.y, sensor3.point.z,
                base_point3.point.x, base_point3.point.y, base_point3.point.z, base_point3.header.stamp.toSec());
            ROS_INFO("sensor4: (%.2f, %.2f. %.2f) -----> map: (%.2f, %.2f, %.2f) at time %.2f",
                sensor4.point.x, sensor4.point.y, sensor4.point.z,
                base_point4.point.x, base_point4.point.y, base_point4.point.z, base_point4.header.stamp.toSec());
*/
        } catch(tf::TransformException& ex){
            ROS_ERROR("Received an exception trying to transform a point from \"base_laser\" to \"base_link\": %s", ex.what());
        }
    }

private:

};

int main(int argc, char** argv){
  ros::init(argc, argv, "ir_transform");

  IrTransform it;

  ros::spin();

  return 0;
}
