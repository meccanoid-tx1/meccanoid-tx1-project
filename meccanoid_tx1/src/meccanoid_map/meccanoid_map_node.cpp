#include <ros/ros.h>

#include "meccanoid_map/map.hpp"
#include <meccanoid_tx1/meccanoid_map.h>
#include <meccanoid_tx1/meccanoid_map_pos.h>


/*
/ Meccanoid map class 
*/
class MeccanoidMap{

  public:
    /*
    / Constructor
    */
    MeccanoidMap(ros::Publisher pub){
        mapPublisher = pub;
        int mapType = -1; // default map representation
        map = new meccanoid_tx1::Map(mapType);
    }

    /*
    / Callback for new obstacles detected
    */
    void obstaclePositionCallback(const meccanoid_tx1::meccanoid_map_posConstPtr& msg){
        meccanoid_tx1::meccanoid_map map_msg = updateTarget(*msg);
        mapPublisher.publish(map_msg);
    }

    /*
    / Callback for new target set
    */
    void targetPositionCallback(const meccanoid_tx1::meccanoid_map_posConstPtr& msg){
        meccanoid_tx1::meccanoid_map map_msg = updateObstacles(*msg);
        mapPublisher.publish(map_msg);
    }

  private:
    ros::Publisher mapPublisher;
    meccanoid_tx1::Map* map; 

    /*
    / Update map target
    */
    meccanoid_tx1::meccanoid_map updateTarget(meccanoid_tx1::meccanoid_map_pos target){
        //TODO: update map target and return as message
        return generateMapMsg(map);
    }

    /*
    / Update map obstacles
    */
    meccanoid_tx1::meccanoid_map updateObstacles(meccanoid_tx1::meccanoid_map_pos obstacle){
        //TODO: update map obstacles and return as message
        return generateMapMsg(map);
    }

    /*
    / Convert map object to a map message which can be published
    */
    meccanoid_tx1::meccanoid_map generateMapMsg(meccanoid_tx1::Map* map){
        meccanoid_tx1::meccanoid_map map_msg;
        //TODO: convert info in map -> map_msg
        return map_msg;
    }
};


/*
/ Meccanoid map node main 
*/
int main(int argc, char **argv)
{
    // init ros
    ros::init(argc, argv, "meccanoid_map");
    ros::NodeHandle nodeHandle;

    // set up map publisher
    ros::Publisher mapPublisher = nodeHandle.advertise<meccanoid_tx1::meccanoid_map>("map", 10);
    
    // set up map
    MeccanoidMap meccanoidMap(mapPublisher);

    // set up subscribers
    ros::Subscriber obstaclePositionSubscriber = nodeHandle.subscribe("/obstacle_position", 1, 
                                                            &MeccanoidMap::obstaclePositionCallback, &meccanoidMap);
    ros::Subscriber targetPositionSubscriber = nodeHandle.subscribe("/target_position", 1, 
                                                            &MeccanoidMap::targetPositionCallback, &meccanoidMap);
    // start ros blocking spin()
    ros::spin();
}
