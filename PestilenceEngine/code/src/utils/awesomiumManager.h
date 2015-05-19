#ifndef AWESOMIUM_MANAGER_H
#define AWESOMIUM_MANAGER_H

#include <Awesomium\include\Awesomium\WebCore.h>
#include <Awesomium\include\Awesomium\BitmapSurface.h>
#include <Awesomium\include\Awesomium\STLHelpers.h>

#define URL "http://www.google.com"

using namespace Awesomium;

class awesomiumManager
{

public:
	awesomiumManager();
	~awesomiumManager();

	WebCore* web_core; 


	void initAwesomium()
	{
		web_core = WebCore::Initialize(WebConfig());

		WebView* myWebView = web_core->CreateWebView(1920, 1080);

		WebURL url(WSLit(URL)); 
		myWebView->LoadURL(url); 

		while (myWebView->IsLoading()) web_core->Update(); 

		// sleep a little and update once more to give scripts a chance to finish loading
		Sleep(300); 
		web_core->Update();

		BitmapSurface* surface = (BitmapSurface*)myWebView->surface(); 

		// make sure surface not null
		if (surface != 0)
		{
			// save bitmapsurgace to jpeg
			surface->SaveToJPEG(WSLit("./result.jpg"));
		}
	}

	void updateAwesomium()
	{
		web_core->Update();
	}

	
};

#endif