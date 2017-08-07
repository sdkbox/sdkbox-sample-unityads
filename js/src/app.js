var HelloWorldLayer = cc.Layer.extend({
    sprite: null,
    ctor: function() {
        //////////////////////////////
        // 1. super init first
        this._super();

        cc.log("Sample Startup")

        this.createTestMenu();

        var winsize = cc.winSize;

        var logo = new cc.Sprite("res/Logo.png");
        var logoSize = logo.getContentSize();
        logo.x = logoSize.width / 2;
        logo.y = winsize.height - logoSize.height / 2;
        this.addChild(logo);

        var quit = new cc.MenuItemLabel(new cc.LabelTTF("QUIT", "sans", 32), function() {
            cc.log("QUIT");
        });
        var menu = new cc.Menu(quit);
        var size = quit.getContentSize();
        menu.x = winsize.width - size.width / 2 - 16;
        menu.y = size.height / 2 + 16;
        this.addChild(menu);

        return true;
    },

    createTestMenu: function() {
        sdkbox.PluginUnityAds.setListener({
            unityAdsDidClick: function(placementId) {
                self.showText('unityAdsDidClick ' + placementId);
            },
            unityAdsPlacementStateChanged: function(placementId, oldState, newState) {
                self.showText('unityAdsPlacementStateChanged:' + placementId + ' oldState:' + oldState + " newState:" + newState);
            },
            unityAdsReady: function(placementId) {
                self.showText('unityAdsReady ' + placementId);
            },
            unityAdsDidError: function(error, message) {
                self.showText('unityAdsDidError:' + error + ' message:' + message);
            },
            unityAdsDidStart: function(placementId) {
                self.showText('unityAdsDidStart=' + placementId);
            },
            unityAdsDidFinish: function(placementId, state) {
                self.showText('unityAdsDidFinish ' + placementId + ' state:' + state);
            }
        });
        sdkbox.PluginUnityAds.init();

        const self = this;
        const size = cc.winSize;

        const coinsLabel = cc.Label.createWithSystemFont("Hello Js", "Arial", 32);
        coinsLabel.setPosition(size.width / 2, 80);
        self.addChild(coinsLabel);
        self.coinsLabel = coinsLabel;

        cc.MenuItemFont.setFontName('arial');
        cc.MenuItemFont.setFontSize(32);

        const printf = console.log

        const menu = new cc.Menu(
            new cc.MenuItemFont("show", function() {
                const placementId = '';
                if (sdkbox.PluginUnityAds.isReady(placementId)) {
                    sdkbox.PluginUnityAds.show(placementId);
                } else {
                    cc.log('unityads is not ready');
                }
            }, this),

            // gc test
            new cc.MenuItemFont("====gc===", function() {
                cc.log("======gc start=====");
                __jsc__.garbageCollect();
                cc.log("======gc end=====");
            })
        );
        menu.setPosition(size.width / 2, size.height / 2);
        menu.alignItemsVerticallyWithPadding(20);
        self.addChild(menu);

        const showText = function(msg) {
            printf(msg);
            self.coinsLabel.setString(msg);
        }
        self.showText = showText;
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter: function() {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});
