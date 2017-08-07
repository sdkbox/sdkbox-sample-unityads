
#include "HelloWorldScene.h"
#include "PluginUnityAds/PluginUnityAds.h"

USING_NS_CC;

#include <vector>
#include <string>
using namespace std;

/******************
 * Show logs
 ******************/
std::vector<std::string> msgbuf;
static void showMsg(const std::string& msg) {
    //
    Label *label = dynamic_cast<Label*>(Director::getInstance()->getNotificationNode());
    if (label == nullptr) {
        auto size = Director::getInstance()->getWinSize();
        label = Label::createWithSystemFont("test", "arial", 16);
        label->setAnchorPoint(Vec2(0,0));
        label->setTextColor(Color4B(0, 255, 0, 255));
        label->setPosition(10, size.height*0.1);
        Director::getInstance()->setNotificationNode(label);
    }

    msgbuf.push_back(msg);
    if (msgbuf.size() > 10) {
        msgbuf.erase(msgbuf.cbegin());
    }


    std::string text = "";
    for (int i = 0; i < msgbuf.size(); i++) {
        stringstream buf;
        buf << i << " " << msgbuf[i] << "\n";
        text = text + buf.str();
    }

    label->setString(text);
}

/******************
 * UnityAds Listener
 ******************/

class UAListener : public sdkbox::UnityAdsListener {
public:
    
    void unityAdsDidClick(const std::string& placementId) {
        showMsg("unityAdsDidClick");
    }

    void unityAdsPlacementStateChanged(const std::string& placementId, sdkbox::PluginUnityAds::SBUnityAdsPlacementState oldState, sdkbox::PluginUnityAds::SBUnityAdsPlacementState newState) {
        showMsg("unityAdsPlacementStateChanged");
    }

    void unityAdsReady(const std::string& placementId) {
        showMsg("unityAdsReady");
    }

    void unityAdsDidError(sdkbox::PluginUnityAds::SBUnityAdsError error, const std::string& message) {
        showMsg("unityAdsDidError");
    }

    void unityAdsDidStart(const std::string& placementId) {
        showMsg("unityAdsDidStart");
    }

    void unityAdsDidFinish(const std::string& placementId, sdkbox::PluginUnityAds::SBUnityAdsFinishState state) {
        showMsg("unityAdsDidFinish");
    }

};

/******************
 * UnityAds sample
 ******************/
Scene* HelloWorld::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ) {
        return false;
    }

    showMsg("Sample Startup");

    // add logo
    auto winsize = Director::getInstance()->getWinSize();
    auto logo = Sprite::create("Logo.png");
    auto logoSize = logo->getContentSize();
    logo->setPosition(Vec2(logoSize.width / 2,
                           winsize.height - logoSize.height / 2));
    addChild(logo);

    // add quit button
    auto label = Label::createWithSystemFont("QUIT", "sans", 32);
    auto quit = MenuItemLabel::create(label, [](Ref*){
        exit(0);
    });
    auto labelSize = label->getContentSize();
    quit->setPosition(Vec2(winsize.width / 2 - labelSize.width / 2 - 16,
                           -winsize.height / 2 + labelSize.height / 2 + 16));
    addChild(Menu::create(quit, NULL));

    // add test menu
    createTestMenu();

    return true;
}

void HelloWorld::createTestMenu() {
    sdkbox::PluginUnityAds::setListener(new UAListener());
    sdkbox::PluginUnityAds::init();

    if (!sdkbox::PluginUnityAds::isSupported()) {
        showMsg("UnityAds is not support this platform");
        return;
    }

    testDemograpicFunctions();

    auto menu = Menu::create();

    menu->addChild(MenuItemLabel::create(Label::createWithSystemFont("Show", "arial", 24), [](Ref*){
        std::string placement = "";
        if (sdkbox::PluginUnityAds::isReady(placement)) {
            sdkbox::PluginUnityAds::show(placement);
        } else {
            showMsg("UnityAds is not ready");
        }
    }));

    menu->alignItemsVerticallyWithPadding(10);
    addChild(menu);
}

void HelloWorld::testDemograpicFunctions() {
}

