#include "game.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

static void printMat(const glm::mat4 mat)
{
	std::cout<<" matrix:"<<std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout<< mat[j][i]<<" ";
		std::cout<<std::endl;
	}
}

Game::Game() : Scene()
{
}

Game::Game(float angle ,float relationWH, float near, float far) : Scene(angle,relationWH,near,far)
{ 	
}

void Game::Init()
{		
	unsigned int texIDs[1] = { 0 }; // pal.png is default texture
	AddShader("../res/shaders/pickingShader");	

	bool for2D = false; // true for using 2D texture, false for 1D
	if (for2D) {
		texIDs[0] = 1; // choosing blankShader.png
		AddShader("../res/shaders/basicShader");
	}
	else {
		AddShader("../res/shaders/basicShader2");
	}
	
	AddTexture("../res/textures/pal.png", for2D); //1D
	AddTexture("../res/textures/blankShader.png", true);


	AddMaterial(texIDs, 1);
	AddShape(Plane,-1,TRIANGLES);
	
	pickedShape = 0;
	
	SetShapeMaterial(0,0);
	MoveCamera(0,zTranslate,10);
	pickedShape = -1;

}

void Game::printPixelWidth(float pixelWidth) {
	std::cout << "Pixel width =  " << pixelWidth << std::endl;

}

void Game::Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx)
{


	Shader *s = shaders[shaderIndx];
	int r = ((pickedShape+1) & 0x000000FF) >>  0;
	int g = ((pickedShape+1) & 0x0000FF00) >>  8;
	int b = ((pickedShape+1) & 0x00FF0000) >> 16;


	static int theR = 32, theG = 32, theB = 32;

	double powColor = pow(2, this->getColor());
	int newR = theR * powColor;
	int newG = theG * powColor;
	int newB = theB * powColor;
	int colorPower = theB * powColor;

	colorPower = glm::clamp(colorPower, 2, 255);
	newR = glm::clamp(newR, 2, 255);
	newG = glm::clamp(newG, 2, 255);
	newB = glm::clamp(newB, 2, 255);	

	textures[materials[shapes[pickedShape]->GetMaterial()]->GetTexture(0)]->Bind(0);
	s->Bind();
	s->SetUniform4f("texCoords",11.0,8.0,177.0,1.0);
	s->SetUniformMat4f("MVP", MVP);
	s->SetUniformMat4f("Normal",Model);

	s->SetUniform1i("p", getP());
	s->SetUniform1i("colorPower", colorPower);



	glm::vec4 coordData = getCoordSize();

	s->SetUniform1f("theMinusX", coordData.x);
	s->SetUniform1f("thePlusX", coordData.y);
	s->SetUniform1f("theMinusY", coordData.z);
	s->SetUniform1f("thePlusY", coordData.w);


	s->SetUniform4f("lightDirection", 0.0f , 0.0f, -1.0f, 0.0f);
	if(shaderIndx == 0)
		s->SetUniform4f("lightColor",r/255.0f, g/255.0f, b/255.0f,1.0f);
	else {
		s->SetUniform4f("lightColor",(float)newR/255, (float)newG / 255,
			(float)newB / 255, 1.0f);
	}

	s->Unbind();
}

void Game::WhenRotate()
{
}

void Game::WhenTranslate()
{
}

void Game::Motion()
{
	if(isActive)
	{
	}
}

Game::~Game(void)
{
}
