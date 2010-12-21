#pragma once

typedef enum 
{
    LIGHT_ID_AMBIENT=-1,
    LIGHT_ID_1=0,
    LIGHT_ID_2,
    LIGHT_ID_3,
    LIGHT_ID_4,
    LIGHT_ID_5,
    LIGHT_ID_6,
    LIGHT_ID_7,
    LIGHT_ID_8,
    MAX_LIGHT
} LightID;

typedef  enum 
{
    LIGHT_TYPE_DIRECTIONAL,
    LIGHT_TYPE_POINT,
    LIGHT_TYPE_SPOT
} LightType;

typedef  enum 
{
    LIGHT_SPACE_VIEW,
    LIGHT_SPACE_LOCAL
} LightSpace;


class LightParams
{
public:

    //light enabled
    bool enabled;
    //type directional,point,spot
    LightType type;
    //local or view space
    LightSpace space;

    //color 0-255 RGB
    int colorR;
    int colorG;
    int colorB;

    //position
    double posX;
    double posY;
    double posZ;

    //direction
    double dirX;
    double dirY;
    double dirZ;
    
    LightParams()
    {
		reset();
	}

	void reset(){
		enabled = false;
		type = LIGHT_TYPE_POINT;
		space = LIGHT_SPACE_VIEW;
		colorR = colorG = colorB = 255;
		posX = posY = posZ = 3;
		dirX = dirY = 0;
		dirZ = -1;
	}

protected:
private:
};
