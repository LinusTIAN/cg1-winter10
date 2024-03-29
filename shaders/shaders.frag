uniform sampler2D tex;	// texture sampler
uniform sampler2D outlineTex;
uniform bool celShade;
uniform int edge_shading_pass;
uniform vec2 screenSize;
uniform int noLighting;

varying vec4 diffuse, ambient, ambientGlobal, eyeVec;
varying vec3 normal, lightDir;
varying float dist;
varying float z;

const float cel_quantum = 0.25;
const float cel_ambient_bias = cel_quantum / 12.5;
const float cel_smooth_band = 0.01;

/* Do lighting calculation with light 0, assuming it is a directional light. */
void directional_light(out vec4 diffColor, out vec4 specColor) {
	diffColor = ambient;
	specColor = vec4(0,0,0,1);
	
	vec3 n = normalize(normal);
	vec3 l = normalize(lightDir);
	float NdotL = dot(n, lightDir);

	if (NdotL > 0.0) {
		vec3 r = -reflect(l, n);
		float RdotEye = max(dot(r, normalize(eyeVec.xyz)), 0.0);
		specColor = gl_FrontMaterial.specular * gl_LightSource[0].specular *
				 	pow(RdotEye, gl_FrontMaterial.shininess);
		diffColor += diffuse * NdotL;
	}
}

/* Do lighting calculation with light 0, assuming it is a point or spot light
   (a point light in OpenGL is a spot-light with the cutoff angle set to 180!). */
void point_spot_light(out vec4 diffColor, out vec4 specColor) {
	diffColor = ambientGlobal;
	specColor = vec4(0,0,0,1);
	
	vec3 n = normalize(normal);
	vec3 l = normalize(lightDir);
	float NdotL = dot(n, l);

	if (NdotL > 0.0) {
		vec3 spotDir = normalize(gl_LightSource[0].spotDirection);
		float spotEffect = dot(spotDir, -l);
		
		if (spotEffect > gl_LightSource[0].spotCosCutoff) {
			spotEffect = pow(spotEffect, gl_LightSource[0].spotExponent);
			float att = spotEffect / (gl_LightSource[0].constantAttenuation +
									  gl_LightSource[0].linearAttenuation * dist +
									  gl_LightSource[0].quadraticAttenuation * dist * dist);
				
			diffColor += att * (diffuse * NdotL + ambient);

			vec3 r = -reflect(l, n);
			float RdotEye = max(dot(r, normalize(eyeVec.xyz)), 0.0);
			specColor = att * gl_FrontMaterial.specular * gl_LightSource[0].specular *
					 	pow(RdotEye, gl_FrontMaterial.shininess);
		}
	}
}

/* Quantize an intensity into discrete intensity bands. Use for cel-shading effect */
vec4 quantize(vec4 i) {
	float min_i = min(i.r, i.g);
		  min_i = min(min_i, i.b);
	float max_i = max(i.r, i.g);
		  max_i = max(max_i, i.b);
	float lightness = (min_i + max_i) / 2.0;
	
	float lower = lightness - mod(lightness, cel_quantum);
	float upper = lower + cel_quantum;

	float f = smoothstep(upper - cel_smooth_band, upper, lightness);
	float quantified = lower + f*cel_quantum + cel_ambient_bias;
	
	return vec4(quantified, quantified, quantified, i.a);
}

const float min_z = 0.96;

/* Called when the alternate "edge-shader" is enabled */
void edge_shader_pass1()
{
	vec3 n = normalize(normal),
		 e = normalize(eyeVec.xyz);
	float NdotE = abs(dot(n, e));
	
	const float near = 0.01,
		 		far = 1.0;
	float linearDepth = (2.0 * near) / (far + near - gl_FragCoord.z * (far - near));
	
	gl_FragColor = vec4(NdotE, 0, linearDepth, 1);
}

void main()
{
	if (edge_shading_pass == 1) {
		edge_shader_pass1();
		return;
	} else if (edge_shading_pass == 2) {
		gl_FragColor = vec4(0,0,0,1);
		return;
	}

	vec4 diff, spec;

	if (gl_LightSource[0].position.w == 0.0)
		directional_light(diff, spec);
	else
		point_spot_light(diff, spec);
		
	if (celShade) {
		diff = quantize(diff);
		spec = quantize(spec);
	}
	
	vec4 texel = texture2D(tex, gl_TexCoord[0].st);
	
	if (edge_shading_pass == 3)
		gl_FragColor = texel * gl_Color;
	else
		gl_FragColor = texel * diff*gl_Color + spec;
}
