#include <ros/ros.h>
#include <pcl/point_cloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/io/pcd_io.h>
#include <pcl_conversions/pcl_conversions.h>
#include <color_cloud_bridge/dummy_pcl.h>
#include <color_cloud_bridge/sensor_and_index.h>


ros::NodeHandle *pnh;
std::string sensor_topic_name;
std::string publish_topic_name;
std::string instance_topic_name;
static int count = 0;
ros::Publisher dummy_pub;
ros::Publisher instance_pub;
int the_number_of_object;

void callback(sensor_msgs::PointCloud2ConstPtr msg)
{
    ROS_INFO_STREAM("callback start");
    pcl::PointCloud<pcl::PointXYZRGB> cloud;
    pcl::fromROSMsg(*msg, cloud);
    if (cloud.points.size() < 1) {
        return;
    }
    ROS_INFO_STREAM("change ros msg to pcl");
    //pcl::io::savePCDFile("/home/ericlab/dummy_cloud/hab.pcd", cloud);
    color_cloud_bridge::dummy_pcl dummy;
    int r_p, g_p, b_p;
    std::vector<int> count(the_number_of_object);
    for (int i = 0; i < cloud.points.size(); i++) {
        r_p = static_cast<int>(cloud.points[i].r);
        g_p = static_cast<int>(cloud.points[i].g);
        b_p = static_cast<int>(cloud.points[i].b);
        dummy.x.push_back(cloud.points[i].x);
        dummy.y.push_back(cloud.points[i].y);
        dummy.z.push_back(cloud.points[i].z);
        dummy.rgb.push_back(cloud.points[i].rgba);
        dummy.r.push_back(r_p);
        dummy.g.push_back(g_p);
        dummy.b.push_back(b_p);
        if (r_p == 255 && b_p == 0 && g_p == 0) {
            dummy.instance.push_back(0);
            count[0]++;
        }
        if (r_p == 0 && b_p == 255 && g_p == 0) {
            dummy.instance.push_back(1);
            count[1]++;
        }
        if (r_p == 0 && b_p == 0 && g_p == 255) {
            dummy.instance.push_back(2);
            count[2]++;
        }
        if (r_p == 255 && b_p == 255 && g_p == 0) {
            dummy.instance.push_back(3);
            count[3]++;
        }
        if (r_p == 0 && b_p == 255 && g_p == 255) {
            dummy.instance.push_back(4);
            count[4]++;
        }
        if (r_p == 255 && b_p == 0 && g_p == 255) {
            dummy.instance.push_back(5);
            count[5]++;
        }
        // if (r_p == 255 && b_p == 255 && g_p == 100) {
        //     dummy.instance.push_back(6);
        //     count[6]++;
        // }
        if (r_p == 255 && b_p == 100 && g_p == 255) {
            dummy.instance.push_back(6);
            count[6]++;
        }
        if (r_p == 100 && b_p == 255 && g_p == 255) {
            dummy.instance.push_back(7);
            count[7]++;
        }
        if (r_p == 255 && b_p == 255 && g_p == 100) {
            dummy.instance.push_back(8);
            count[8]++;
        }
        if (r_p == 100 && b_p == 100 && g_p == 255) {
            dummy.instance.push_back(9);
            count[9]++;
        }
        if (r_p == 255 && b_p == 100 && g_p == 100) {
            dummy.instance.push_back(10);
            count[10]++;
        }
        if (r_p == 100 && b_p == 255 && g_p == 100) {
            dummy.instance.push_back(11);
            count[11]++;
        }
        if (r_p == 150 && b_p == 100 && g_p == 255) {
            dummy.instance.push_back(12);
            count[12]++;
        }
        if (r_p == 100 && b_p == 150 && g_p == 255) {
            dummy.instance.push_back(13);
            count[13]++;
        }
        if (r_p == 255 && b_p == 100 && g_p == 150) {
            dummy.instance.push_back(14);
            count[14]++;
        }
        if (r_p == 255 && b_p == 150 && g_p == 100) {
            dummy.instance.push_back(15);
            count[15]++;
        }
        if (r_p == 100 && b_p == 255 && g_p == 150) {
            dummy.instance.push_back(16);
            count[16]++;
        }
        if (r_p == 150 && b_p == 255 && g_p == 100) {
            dummy.instance.push_back(17);
            count[17]++;
        }
        if (r_p == 100 && b_p == 150 && g_p == 0) {
            dummy.instance.push_back(18);
            count[18]++;
        }
        if (r_p == 150 && b_p == 100 && g_p == 0) {
            dummy.instance.push_back(19);
            count[19]++;
        }
        if (r_p == 150 && b_p == 0 && g_p == 100) {
            dummy.instance.push_back(20);
            count[20]++;
        }
        if (r_p == 100 && b_p == 0 && g_p == 150) {
            dummy.instance.push_back(21);
            count[21]++;
        }
        if (r_p == 0 && b_p == 100 && g_p == 150) {
            dummy.instance.push_back(22);
            count[22]++;
        }
        if (r_p == 0 && b_p == 150 && g_p == 100) {
            dummy.instance.push_back(23);
            count[23]++;
        }
        if (r_p == 255 && b_p == 150 && g_p == 150) {
            dummy.instance.push_back(24);
            count[24]++;
        }
        if (r_p == 255 && b_p == 255 && g_p == 255) {
            dummy.instance.push_back(25);
            count[25]++;
        }
    }

    for (int i = 0; i < 10; i++) {
        ROS_INFO_STREAM("x: " << dummy.x[i*10] << "  y: " << dummy.y[i*10] << "  z: " << dummy.z[i*10] << "  rgb: " << dummy.rgb[i*10]);
    }
    for (int i = 0; i < 10; i++) {
        ROS_INFO_STREAM("pointcloud  rgba:"<< cloud.points[i].rgba);
        std::cout << "  r: " << static_cast<int>(cloud.points[i*100].r) << "  b: " << static_cast<int>(cloud.points[i*100].b) << "  g " << static_cast<int>(cloud.points[i*10].g) << std::endl;;
    }
    ROS_INFO_STREAM("publish start");
    dummy_pub.publish(dummy);
    dummy.x.clear();
    dummy.y.clear();
    dummy.z.clear();
    dummy.rgb.clear();
    ROS_INFO_STREAM("finish");
    for (int i = 0; i < the_number_of_object; i++) {
        ROS_INFO_STREAM(std::to_string(i) << ":  " << std::to_string(count[i]));
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "color_bridge");
    ros::NodeHandle nh;
    pnh = new ros::NodeHandle("~");
    pnh->getParam("sensor_topic_name", sensor_topic_name);
    pnh->getParam("publish_topic_name", publish_topic_name);
    pnh->getParam("the_number_of_object", the_number_of_object);
    dummy_pub = nh.advertise<color_cloud_bridge::dummy_pcl>(publish_topic_name, 10);
    instance_pub = nh.advertise<color_cloud_bridge::sensor_and_index>(instance_topic_name, 10);
    ros::Subscriber sub;
    sub = nh.subscribe(sensor_topic_name, 10, callback);
    ros::spin();
    return 0;
}