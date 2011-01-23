varying vec4 diffuse, ambient, ambientGlobal, eyeVec;
varying vec3 normal, lightDir, halfVector;
varying float dist;

/* Do lighting calculation with light 0, assuming it is a directional light. */
void directional_light() {
	normal = normalize(gl_NormalMatrix * gl_Normal);
	halfVector = normalize(gl_LightSource[0].halfVector.xyz);
	lightDir = normalize(gl_LightSource[0].position.xyz);
	
	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	ambient += gl_LightModel.ambient * gl_FrontMaterial.ambient;
}

/* 	Do lighting calculation with light 0, assuming it is a point light or spot light
	(the per-vertex calculations are the same for both). */
void point_spot_light() {	
	normal = normalize(gl_NormalMatrix * gl_Normal);
	vec4 lightVector = gl_LightSource[0].position - gl_ModelViewMatrix*gl_Vertex;
	lightDir = normalize(lightVector.xyz);
	
	/* compute the distance to the light source to a varying variable*/
	dist = length(lightVector);

	halfVector = normalize(gl_LightSource[0].halfVector.xyz);
	
	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient;
} 

void main()
{
	if (gl_LightSource[0].position.w == 0.0)
		directional_light();
	else
		point_spot_light();
	
	eyeVec = -(gl_ModelViewMatrix * gl_Vertex);
	gl_TexCoord[0] = gl_MultiTexCoord0;	// generate texture coordinates
	gl_Position = ftransform();
	gl_FrontColor = gl_BackColor = gl_Color/*vec4(0,1,0,1)*/;
} 
