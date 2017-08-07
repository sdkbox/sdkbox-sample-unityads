
local MainScene = class("MainScene", cc.load("mvc").ViewBase)

function MainScene:onCreate()
    print("Sample Startup")

    local label = cc.Label:createWithSystemFont("QUIT", "sans", 32)
    local quit = cc.MenuItemLabel:create(label)
    quit:onClicked(function()
        os.exit(0)
    end)
    local size = label:getContentSize()
    local menu = cc.Menu:create(quit)
    menu:setPosition(display.right - size.width / 2 - 16, display.bottom + size.height / 2 + 16)
    self:addChild(menu)

    self:setupTestMenu()
end

function MainScene:setupTestMenu()
    self.status =
    cc.Label:createWithSystemFont("Hello Lua", "Arial", 32)
            :move(display.cx, 100)
            :addTo(self)
    self.status:setColor(cc.c3b(255, 0, 0))
    local showText = function(msg)
        printf(msg)
        self.status:setString(msg)
    end

    cc.MenuItemFont:setFontName("Arial")
    cc.Menu:create(
                   cc.MenuItemFont:create("show"):onClicked(function ()
                        local placement = ""
                        if (sdkbox.PluginUnityAds:isReady(placement)) then
                            sdkbox.PluginUnityAds:show(placement)
                        else
                            printf("unityads ad is not ready")
                        end
                   end)
                   )
        :move(display.cx, display.cy)
        :addTo(self)
        :alignItemsVerticallyWithPadding(20)

    require('cocos.cocos2d.json')
    local plugin = sdkbox.PluginUnityAds
    plugin:setListener(function(args)
        local event = args.event
        showText(event)
        dump(args, "unityads listener info:")
    end)
    plugin:init()

end

return MainScene
