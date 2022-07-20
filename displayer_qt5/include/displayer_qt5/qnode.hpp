/**
 * @file /include/displayer_qt5/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef displayer_qt5_QNODE_HPP_
#define displayer_qt5_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

// To workaround boost/qt4 problems that won't be bugfixed. Refer to
//    https://bugreports.qt.io/browse/QTBUG-22829
#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif
#include <string>
#include <QThread>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <QImage>
#include <radar_msgs/game_state.h>
#include <radar_msgs/referee_warning.h>
#include <radar_msgs/supply_projectile_action.h>
#include <QListWidgetItem>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace displayer_qt5 {

/*****************************************************************************
** Class
*****************************************************************************/
enum LogLevel
{
         Debug,
         Info,
         Warn,
         Error,
         Fatal
};
struct log_information
{
         LogLevel level;
         QString qstring;
};
struct robot
{
    int hpCurrent;
    int hpMax;
};
class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
	bool init();
    void run();
    void imgShowCallback(const sensor_msgs::ImageConstPtr& msg);//camera callback function
    void imgSensorFarCallback(const sensor_msgs::ImageConstPtr& msg);
    void imgSensorCloseCallback(const sensor_msgs::ImageConstPtr& msg);
    void gameStateCallback(const radar_msgs::game_stateConstPtr& msg);
    void supplyProjectileActionCallback(const radar_msgs::supply_projectile_actionConstPtr& msg);
    void refereeWarningCallback(const radar_msgs::referee_warningConstPtr& msg);
    void pubCelibrateResult();
    QImage image;
    QImage imageSensorFar;
    QImage imageSensorClose;
    QImage imageCalibrateMainWindow;
    QImage imageCalibrateSecondWindow;
    QImage imageSmallMap;
    QImage imageLogo;
    QImage imageShowSecondWindow;
    QListWidgetItem *listWidgetItem;
    log_information *logInformation;
	void log( const LogLevel &level, const std::string &msg);
    void loadParams();
    QString sensorFarImgRaw;
    QString sensorCloseImgRaw;
    QString cameraCelibrating;
    QPoint mouseLoaction;
    bool if_is_celibrating;
    QString realsenseImgRaw;
    QPoint sensor_far_points[4];
    QPoint sensor_close_points[4];
    QString calibrationTopicSensorFar;
    QString calibrationTopicSensorClose;
    QString gameProgress;
    int stageRemainTime;
    int calibrateRate;
    int calibrateMainWindowWidth;
    int calibrateMainWindowHeight;
    int calibrateSecondWindowWidth;
    int calibrateSecondWindowHeight;
    int showMainWindowWidth;
    int showMainWindowHeight;
    int showSecondWindowWidth;
    int showSecondWindowHeight;
    int smallMapWidth;
    int smallMapHeight;
    int logoWidth;
    int logoHeight;
    cv::Mat img;
    cv::Mat imgSensorFar;
    cv::Mat imgSensorClose;
    cv::Mat imgSmallMap;
    cv::Mat imgLogo;
    cv::Mat imgShowSecondWindow;
    std::string battle_color;
    robot robot_red1;
    robot robot_red2;
    robot robot_red3;
    robot robot_red4;
    robot robot_red5;
    robot robot_redGuard;
    robot robot_redOutpose;
    robot robot_redBase;
    robot robot_blue1;
    robot robot_blue2;
    robot robot_blue3;
    robot robot_blue4;
    robot robot_blue5;
    robot robot_blueGuard;
    robot robot_blueOutpose;
    robot robot_blueBase;

Q_SIGNALS:
    void loggingUpdated();
    void rosShutdown();
    void loggingCamera();//发出设置相机图片信号
    void loggingCameraCalibrateMainWindow();
    void loggingCameraCalibrateSecondWindow();
    void loggingGameStateUpdate();

private:
	int init_argc;
	char** init_argv;
    image_transport::Subscriber image_sub;
    image_transport::Subscriber image_sub_sensor_far;
    image_transport::Subscriber image_sub_sensor_close;
    ros::Publisher calibration_pub_sensor_far;
    ros::Publisher calibration_pub_sensor_close;
    std::string gameStateTopic;
    std::string supplyProjectileActionTopic;
    std::string refereeWarningTopic;
    ros::Subscriber gameStateSub;
    ros::Subscriber supplyProjectileActionSub;
    ros::Subscriber refereeWarningSub;
};

}  // namespace displayer_qt5

#endif /* displayer_qt5_QNODE_HPP_ */
