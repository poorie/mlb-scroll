/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MyScroll.h"

#include <string>
#include <fstream>
#include <streambuf>
#include <nlohmann/json.hpp>
#include <statsapi.hpp>
#include <algorithm>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <extensions/cocos-ext.h>
#include <network/HttpClient.h>

USING_NS_CC; // this means using namespace cocos2d.

//Defines
#define POSTERS_ONSCREEN 5
#define POSTER_MIDPOINT 2
#define RELATIVE_BOX_CHILD_ORDER_TITLE 1
#define RELATIVE_BOX_CHILD_ORDER_IMAGE 2
#define RELATIVE_BOX_CHILD_ORDER_BLURB 3

Scene* MyScroll::createScene()
{
    return MyScroll::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MyScroll.cpp\n");
}

void MyScroll::loadImage(std::string url)
{
    log("loading new posters: %s", url.c_str());
	log("onHttpRequestCompleted In the request");
	cocos2d::network::HttpRequest* request = new (std::nothrow) cocos2d::network::HttpRequest();
	request->setUrl(url.c_str());
	request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	request->setResponseCallback(CC_CALLBACK_2(MyScroll::onRequestImgCompleted, this));
	request->setTag("Post test2");
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();
}

void MyScroll::onRequestImgCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
	log("AppDelegate::onHttpRequestCompleted - onHttpRequestCompleted BEGIN");
	if (!response)
	{
		log("onHttpRequestCompleted - No Response");
		return;
	}

	log("onHttpRequestCompleted - Response code: %lu", response->getResponseCode());

	if (!response->isSucceed())
	{
		log("onHttpRequestCompleted - Response failed");
		log("onHttpRequestCompleted - Error buffer: %s", response->getErrorBuffer());
		return;
	}
	log("onHttpRequestCompleted - Response code: %s", response->getResponseDataString());

	std::vector<char> *buffer = response->getResponseData();
	const char* file_char = buffer->data();
    Image * image = new  Image ();
	image-> initWithImageData ( reinterpret_cast<const unsigned char*>(&(buffer->front())), buffer->size());
	Texture2D * texture = new  Texture2D ();
	texture-> initWithImage (image);

	Sprite * poster = Sprite :: createWithTexture (texture);
    auto origin = Director::getInstance()->getVisibleOrigin(); // Origin is at bottom left corner
    auto winSize = Director::getInstance()->getVisibleSize();
    poster->setPosition(Vec2(origin.x + (winSize.width * 0.75), origin.y + (winSize.height * 0.75)));
    this->removeChildByName("poster");
	this->addChild(poster, 0, "poster");

	log("onHttpRequestCompleted height %f", poster->getContentSize().height);
}

void MyScroll::onRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
	if (!response)
	{
		log("onHttpRequestCompleted - No Response");
		return;
	}
	log("onHttpRequestCompleted - Response code: %lu", response->getResponseCode());
	if (!response->isSucceed())
	{
		log("onHttpRequestCompleted - Response failed");
		log("onHttpRequestCompleted - Error buffer: %s", response->getErrorBuffer());
		return;
	}
	log("onHttpRequestCompleted - Response code: %s", response->getResponseDataString());

	std::vector<char> *buffer = response->getResponseData();
    std::string body(buffer->begin(), buffer->end());
    //response->release();
	
    quicktype::StatsApi data = nlohmann::json::parse(body);

    if (data.total_games) {
        this->totalGames = *data.total_games.get();
    } else {
        this->totalGames = 0;
    }

    cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){

        this->listView->removeAllChildrenWithCleanup(true);
        this->imageUrls.clear();
        this->selectedIndex = 0;
        // 5. b Setup buttons for scrolling inside this list
        for (int i = 0; i < this->totalGames; i++)
        {
            ui::RelativeBox *relativeBox = ui::RelativeBox::create();
            //This makes child 1, 2 3 align horizontal as we need it to be
            relativeBox->setLayoutType(ui::RelativeBox::Type::VERTICAL);

            // Title
            std::string teams = "";
            std::vector<quicktype::Game> games = (*(*data.dates.get())[0].games.get());
            std::string team1 = (*(*(*(*games[i].teams.get()).away.get()).team.get()).name.get());
            std::string team2 = (*(*(*(*games[i].teams.get()).home.get()).team.get()).name.get());
            teams = team1 + "\nat " + team2;
            ui::Text *textTitle = ui::Text::create(teams, "fonts/Tahoma Regular font.ttf", 30.0);
            if (0 == i) {
                textTitle->setVisible(true);
            } else {
                textTitle->setVisible(false);
            }
            relativeBox->addChild(textTitle, 1, "textTitle");
            textTitle->setColor(Color3B::RED);
            textTitle->setTextHorizontalAlignment(TextHAlignment::CENTER);
            textTitle->setTextVerticalAlignment(TextVAlignment::TOP);
            textTitle->setPositionType(ui::Widget::PositionType::PERCENT);
            textTitle->setPositionX(50.0);
            textTitle->enableShadow(Color4B::BLACK, Size(2,-2), 1);
            textTitle->enableOutline(Color4B::BLACK, 1);
            textTitle->enableGlow(Color4B::BLACK);          

            // Grid Image
            ui::ImageView *gridImage = ui::ImageView::create();
            if(0 == i) {
                gridImage->loadTexture("mlb-classic-medium-focused.png");
            } else {
                gridImage->loadTexture("mlb-classic-medium-normal.png");
            }            

            relativeBox->addChild(gridImage, 2, "gridImage");

            // Text Body
            std::string body = "Data not available at the moment.";
            std::shared_ptr<std::string> srcUrl;
            quicktype::Content content = (*games[i].content.get());
            if(content.editorial){
                auto mlb = (*(*content.editorial.get()).recap.get()).mlb;
                if (mlb) {
                    body = (*(*mlb.get()).blurb.get());
                    srcUrl = (*(*(*mlb.get()).photo.get()).cuts.get())[7].src;

                    int wordCount = 0;
                    for (auto str = body.begin(); str != body.end(); str = std::find(str, body.end(), ' ')) {
                        str++;
                        wordCount++;
                        if (wordCount <= 20) {
                            continue;
                        }
                        body = std::string(body.begin(), str) + "...";
                        break;
                    }
                }
            }
            ui::Text *textBody = ui::Text::create(body, "fonts/Tahoma Regular font.ttf", 18.0);
            if (0 == i) {
                textBody->setVisible(true);
            } else {
                textBody->setVisible(false);
            }
            textBody->setColor(Color3B::WHITE);
            textBody->setTextAreaSize(Size(300.0, 350.0));
            textBody->setTextHorizontalAlignment(TextHAlignment::CENTER);
            textBody->setTextVerticalAlignment(TextVAlignment::TOP);
            textBody->enableShadow(Color4B::BLACK, Size(2,-2), 1);
            textBody->enableOutline(Color4B::BLACK, 1);
            textBody->enableGlow(Color4B::BLACK);

            this->imageUrls.push_back(srcUrl);

            relativeBox->addChild(textBody, 3, "textBody");
            
            log("adding relativeBox to child %d", i);
            listView->addChild(relativeBox);
        }
        if(this->totalGames > 0){
            //Update poster image if available
            std::shared_ptr<std::string> url = this->imageUrls[this->selectedIndex];
            if (url) {
                this->loadImage(*url.get());
            }   
        }
        this->listView->forceDoLayout();     
    });
}

void MyScroll::loadContent() {
    ui::ListView *listView = this->listView;

    cocos2d::network::HttpRequest* request = new (std::nothrow) cocos2d::network::HttpRequest();
    std::ostringstream fmtDate;
    fmtDate.imbue(std::locale("en_US.utf-8"));
    fmtDate << std::put_time(&this->selectedDate, "%Y-%m-%d");
    std::string url = "http://statsapi.mlb.com/api/v1/schedule?hydrate=game(content(editorial(recap))),decisions&date=" + fmtDate.str() + "&sportId=1";
	request->setUrl(url);
	request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	request->setResponseCallback(CC_CALLBACK_2(MyScroll::onRequestCompleted, this));
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();

    //1. Get the data! Open and read statsapi.json
    //std::ifstream t("/home/alex/CppProjects/MyScroll/statsapi.json");
    //std::string str;

    //t.seekg(0, std::ios::end);
    //str.reserve(t.tellg());
    //t.seekg(0, std::ios::beg);

    //str.assign((std::istreambuf_iterator<char>(t)),
     //           std::istreambuf_iterator<char>());
    //t.close();
}

// on "init" you need to initialize your instance
bool MyScroll::init()
{
    // 2. Call the super class’s init method. Only if this succeeds do you proceed with MyScroll's setup.
    if ( !Scene::init() ) {
            return false;
    }

      // 3. You then get the window’s bounds using the game’s Director singleton.
    auto origin = Director::getInstance()->getVisibleOrigin(); // Origin is at bottom left corner
    auto winSize = Director::getInstance()->getVisibleSize();
    
    printf("#########################################\n");
    printf("Origin metrics: x<%f> y<%f>\n", origin.x, origin.y );
    printf("winSize metrics: width<%f> height<%f>\n", winSize.width, winSize.height );
    printf("\n#########################################\n");

    // 5.a Setup list
    ui::ListView *listView = ui::ListView::create();
    log("Setting listView to x<%f> y<%f>", (winSize.width * 0.05) + origin.x, (winSize.height * 0.60) + origin.y);
    listView->setPosition(Vec2((winSize.width * 0.05) + origin.x, (winSize.height * 0.60) + origin.y));
    listView->setItemsMargin(115.0);
    listView->setContentSize(Size(winSize.width, winSize.height));
    //Did this change anything?
    listView->setInnerContainerSize(Size(winSize.width * (this->totalGames * 1.0 / POSTERS_ONSCREEN), winSize.height));

    listView->setAnchorPoint(Vec2(0,0.5));
    //Scroll direction
    listView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    listView->setScrollBarEnabled(false);
    listView->setLayoutType(ui::Layout::Type::HORIZONTAL);

    // 3 Set background
    auto background = Sprite::create("mlb-stadium-background.jpg");
    if (background == nullptr)
    {
        problemLoading("mlb-stadium-background.jpg");
    }
    else
    {
        // position the sprite on the center of the screen
        background->setPosition(Vec2(winSize.width/2 + origin.x, winSize.height/2 + origin.y));
        //Scale it to designResolution?
        background->setContentSize(Size(winSize.width, winSize.height));
        // add the sprite as a child to this layer
        this->addChild(background, 0);
    }

    // 4 Date that the game is from
    std::istringstream ss("2019-06-04");
    ss.imbue(std::locale("en_US.utf-8"));
    ss >> std::get_time(&this->selectedDate, "%Y-%m-%d");
    std::ostringstream fmtDate;
    fmtDate.imbue(std::locale("en_US.utf-8"));
    fmtDate << std::put_time(&this->selectedDate, "%Y-%m-%d");
    std::string dateTxt = "Games from "+ fmtDate.str();
    ui::Text *dateField = ui::Text::create(dateTxt, "fonts/Tahoma Regular font.ttf", 25.0);
    log("\nTrying to place date here: x<%f> y<%f>",(winSize.width * 0.15) + origin.x, (winSize.height * 0.75) + origin.y);
    dateField->setPosition(Vec2((winSize.width * 0.15) + origin.x, (winSize.height * 0.75) + origin.y));
    dateField->enableShadow(Color4B::BLACK, Size(2,-2), 1);
    dateField->enableOutline(Color4B::BLACK, 1);
    dateField->enableGlow(Color4B::BLACK);

    this->addChild(dateField, 0, "dateField");

    this->addChild(listView);
    this->listView = listView;

    //Start with focused index at 0
    this->selectedIndex = 0;

    // Add listening for keyboard keys
    auto eventListener = cocos2d::EventListenerKeyboard::create();

    eventListener->onKeyPressed = std::bind(&MyScroll::handleKeyPress, this, std::placeholders::_1, std::placeholders::_2);

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

    std::thread(std::bind(&MyScroll::loadContent, this)).detach();

    return true;
}

void MyScroll::handleKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, Event* event) {
    Vec2 loc = event->getCurrentTarget()->getPosition();
    switch(keyCode){
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_A:
            {
                log("KEY left or A");
                //lower on the indexx
                if(this->selectedIndex == 0)
                {
                    log("cant go any more left");

                    return;
                }
                //Defocus the current one
                ui::RelativeBox *relativeBoxCurrent = static_cast<ui::RelativeBox *>(this->listView->getItems().at(this->selectedIndex));
                ui::Text *textTitleCurrent = static_cast<ui::Text *>(relativeBoxCurrent->getChildByName("textTitle"));
                textTitleCurrent->setVisible(false);
                ui::ImageView *imageCurrent = static_cast<ui::ImageView *>(relativeBoxCurrent->getChildByName("gridImage"));
                imageCurrent->loadTexture("mlb-classic-medium-normal.png");
                ui::Text *textBodyCurrent = static_cast<ui::Text *>(relativeBoxCurrent->getChildByName("textBody"));
                textBodyCurrent->setVisible(false);

                //Decrease the selected index
                this->selectedIndex--;

                //Focus the next one
                ui::RelativeBox *relativeBoxLeft = static_cast<ui::RelativeBox *>(this->listView->getItems().at(this->selectedIndex));
                ui::Text *textTitleLeft = static_cast<ui::Text *>(relativeBoxLeft->getChildByName("textTitle"));
                textTitleLeft->setVisible(true);
                ui::ImageView *imageLeft = static_cast<ui::ImageView *>(relativeBoxLeft->getChildByName("gridImage"));
                imageLeft->loadTexture("mlb-classic-medium-focused.png");
                ui::Text *textBodyLeft = static_cast<ui::Text *>(relativeBoxLeft->getChildByName("textBody"));
                textBodyLeft->setVisible(true);

                //Scroll if necessary
                this->listView->scrollToPercentHorizontal(this->selectedIndex * 100.0 / (this->totalGames -1), 0.125, false);
                this->listView->forceDoLayout();

                //Update poster image if available
                std::shared_ptr<std::string> url = this->imageUrls[this->selectedIndex];
                if (url) {
                    this->loadImage(*url.get());
                }
            }
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_D:
            {
                log("KEY right or D");
                if(this->selectedIndex == (this->totalGames - 1))
                {
                    log("cant go any more right");

                    return;
                }

                //Defocus the current one
                ui::RelativeBox *relativeBoxCurrent = static_cast<ui::RelativeBox *>(this->listView->getItems().at(this->selectedIndex));
                ui::Text *textTitleCurrent = static_cast<ui::Text *>(relativeBoxCurrent->getChildByName("textTitle"));
                textTitleCurrent->setVisible(false);
                ui::ImageView *imageCurrent = static_cast<ui::ImageView *>(relativeBoxCurrent->getChildByName("gridImage"));
                imageCurrent->loadTexture("mlb-classic-medium-normal.png");
                ui::Text *textBodyCurrent = static_cast<ui::Text *>(relativeBoxCurrent->getChildByName("textBody"));
                textBodyCurrent->setVisible(false);

                //Increase selected index
                this->selectedIndex++;

                //Focus the next one
                ui::RelativeBox *relativeBoxRight = static_cast<ui::RelativeBox *>(this->listView->getItems().at(this->selectedIndex));
                ui::Text *textTitleRight = static_cast<ui::Text *>(relativeBoxRight->getChildByName("textTitle"));
                textTitleRight->setVisible(true);
                ui::ImageView *imageRight = static_cast<ui::ImageView *>(relativeBoxRight->getChildByName("gridImage"));
                imageRight->loadTexture("mlb-classic-medium-focused.png");
                ui::Text *textBodyRight = static_cast<ui::Text *>(relativeBoxRight->getChildByName("textBody"));
                textBodyRight->setVisible(true);

                //Scroll if necessary
                this->listView->scrollToPercentHorizontal(this->selectedIndex * 100.0 / (this->totalGames - 1), 0.125, false);
                this->listView->forceDoLayout();

                //Update poster image if available
                std::shared_ptr<std::string> url = this->imageUrls[this->selectedIndex];
                if (url) {
                    this->loadImage(*url.get());
                }                
            }
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_W:
            {
                log("KEY up or W");
                time_t toDate = mktime(&this->selectedDate);
                toDate += 60 * 60 * 24;
                this->selectedDate = *std::gmtime(&toDate);
                ui::Text *dateField = static_cast<ui::Text*>(this->getChildByName("dateField"));
                std::ostringstream fmtDate;
                fmtDate.imbue(std::locale("en_US.utf-8"));
                fmtDate << std::put_time(&this->selectedDate, "%Y-%m-%d");
                std::string dateTxt = "Games from "+ fmtDate.str();
                dateField->setString(dateTxt);
                std::thread(std::bind(&MyScroll::loadContent, this)).detach();
            }
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_S:
            {
                log("KEY down or S");
                time_t toDate = mktime(&this->selectedDate);
                toDate -= 60 * 60 * 24;
                this->selectedDate = *std::gmtime(&toDate);
                ui::Text *dateField = static_cast<ui::Text*>(this->getChildByName("dateField"));
                std::ostringstream fmtDate;
                fmtDate.imbue(std::locale("en_US.utf-8"));
                fmtDate << std::put_time(&this->selectedDate, "%Y-%m-%d");
                std::string dateTxt = "Games from "+ fmtDate.str();
                dateField->setString(dateTxt);
                std::thread(std::bind(&MyScroll::loadContent, this)).detach();
            }
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_Q:
            Director::getInstance()->end();
            //std::exit(0);
            break;
    }
}

void MyScroll::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
