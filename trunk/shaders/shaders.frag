varying vec4 diffuse, ambient, ambientGlobal, eyeVec;
varying vec3 normal, lightDir;
varying float dist;
uniform sampler2D tex;	// texture sampler

/* Do lighting calculation with light 0, assuming it is a directional light. */
vec4 directional_light() {
	vec4 color = ambient;
	
	vec3 n = normalize(normal);
	vec3 l = normalize(lightDir);
	float NdotL = dot(n, lightDir);

	if (NdotL > 0.0) {
		vec3 r = -reflect(l, n);
		float RdotEye = max(dot(r, normalize(eyeVec.xyz)), 0.0);
		color += gl_FrontMaterial.specular * gl_LightSource[0].specular *
				 pow(RdotEye, gl_FrontMaterial.shininess);
		color += diffuse * NdotL;
	}

	return color;
}

/* Do lighting calculation with light 0, assuming it is a point or spot light
   (a point light in OpenGL is a spot-light with the cutoff angle set to 180!). */
vec4 point_spot_light() {
	vec4 color = ambientGlobal;
	
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
				
			color += att * (diffuse * NdotL + ambient);

			vec3 r = -reflect(l, n);
			float RdotEye = max(dot(r, normalize(eyeVec.xyz)), 0.0);
			color += att * gl_FrontMaterial.specular * gl_LightSource[0].specular *
					 pow(RdotEye, gl_FrontMaterial.shininess);
		}
	}

	return color;
}

/* Quantify an intensity into discrete intensity bands. Use for cel-shading effect */
vec4 quantify(vec4 i) {
	const float quantum = 0.333333;

	float min_i = min(i.r, i.g);
		  min_i = min(min_i, i.b);
	float max_i = max(i.r, i.g);
		  max_i = max(max_i, i.b);
	float lightness = (min_i + max_i) / 2.0;
	
	float quantified = lightness - mod(lightness, quantum);
	
	return vec4(quantified, quantified, quantified, i.a);
}

void main()
{
	vec4 intensity;

	if (gl_LightSource[0].position.w == 0.0)
		intensity = directional_light();
	else
		intensity = point_spot_light();
	
	vec4 texel = texture2D(tex, gl_TexCoord[0].st);
	gl_FragColor = /*vec4(texel.rgb, 1) * */intensity * gl_Color;
}
