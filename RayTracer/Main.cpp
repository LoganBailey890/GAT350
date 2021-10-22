#include "Renderer.h"
#include "Framebuffer.h"
#include "Image.h"
#include "PostProcess.h"

#include <iostream>
#include <SDL.h>

int main(int, char**)
{
	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	renderer->Initialize(WIDTH, HEIGHT);
	
	std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(renderer.get(),renderer->width, renderer->height);


	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
		framebuffer->Clear({ 0,0,0,0 });

        //for (int i = 0; i < 100; i++)
        //{
        //    framebuffer->DrawPoint(rand() % framebuffer->colorBuffer.width, rand() % framebuffer->colorBuffer.height, { 0, 255, 0, 0 });
        //}
        for (int i = 0; i < 20; i++)
        {
            framebuffer->DrawRect(rand() % framebuffer->colorBuffer.width, rand() % framebuffer->colorBuffer.height, 20, 20, { (uint8_t)(rand() % 2 * 255),(uint8_t)(rand() % 2 * 255), (uint8_t)(rand() % 2 * 255), (uint8_t)(rand()% 256) });
        }
        //for (int i = 0; i < 20; i++)
        //{
        //    framebuffer->DrawLine(framebuffer->colorBuffer.width >> 1, framebuffer->colorBuffer.height >> 1, rand() % framebuffer->colorBuffer.width, rand() % framebuffer->colorBuffer.height, { 255, 255, 255, 0 });
        //}
        //for (int i = 0; i < 20; i++) 
        //{
        //    framebuffer->DrawCircle(rand() % framebuffer->colorBuffer.width, rand() % framebuffer->colorBuffer.height, 10, { 145,135,54,255 });
        //}
        //framebuffer->DrawTriangle(300, 350, 350, 400, 250, 400, { 23,145,254,255 });



        //for (int i = 0; i < 10; i++)
        //{
        //    framebuffer->DrawQuadraticCurve(
        //        rand() % framebuffer->colorBuffer.width, rand() % framebuffer->colorBuffer.height,
        //        rand() % framebuffer->colorBuffer.width, rand() % framebuffer->colorBuffer.height,
        //        rand() % framebuffer->colorBuffer.width, rand() % framebuffer->colorBuffer.height, 30, { 255, 255, 0, 255 });
        //}
        //for (int i = 0; i < 10; i++)
        //{
        //    framebuffer->DrawCubicCurve(
        //        rand() % framebuffer->colorBuffer.width, rand() % framebuffer-> colorBuffer.height,
        //        rand() % framebuffer->colorBuffer.width, rand() % framebuffer->colorBuffer.height,
        //        rand() % framebuffer->colorBuffer.width, rand() % framebuffer->colorBuffer.height,
        //        rand() % framebuffer->colorBuffer.width, rand() % framebuffer->colorBuffer.height,
        //        30, { 0, 255, 255, 255 });
        //}

        std::unique_ptr<Image> image = std::make_unique<Image>();
        image->Load("../resources/sus.bmp",200);
        image->Flip();
        framebuffer->DrawImage(300, 50, image.get());
        //PostProcess::Invert(framebuffer->colorBuffer);
        //PostProcess::Noise(framebuffer->colorBuffer, 50);
        //PostProcess::MonoChrome(framebuffer->colorBuffer);
        //PostProcess::Brightness(framebuffer->colorBuffer, 50);
        // PostProcess::ColorBalance(framebuffer->colorBuffer, 0, 0, 80);
        //PostProcess::Threshold(framebuffer->colorBuffer, 200);
        std::unique_ptr<Image> image1 = std::make_unique<Image>(*image.get());
        PostProcess::BoxBlur(image1->colorBuffer);
        framebuffer->DrawImage(0, 300, image1.get());
        std::unique_ptr<Image> image2 = std::make_unique<Image>(*image.get());
        PostProcess::GausianBlur(image2->colorBuffer);
        framebuffer->DrawImage(200, 300, image2.get());
        std::unique_ptr<Image> image3 = std::make_unique<Image>(*image.get());
        PostProcess::Sharpen(image3->colorBuffer);
        framebuffer->DrawImage(400, 300, image3.get());
        std::unique_ptr<Image> image4 = std::make_unique<Image>(*image.get());
        PostProcess::MonoChrome(image4->colorBuffer);
        PostProcess::Edge(image4->colorBuffer, 0);
        framebuffer->DrawImage(600, 300, image4.get());




		framebuffer->Update();

		renderer->CopyBuffer(framebuffer.get());

		renderer->Present();
	}

	SDL_Quit();

	return 0;
}
