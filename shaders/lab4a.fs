
#version 130

in vec3 normal;
in vec3 position;
uniform vec4 colour;
uniform vec3 Eye;
uniform vec3 light;
uniform vec4 material;

void main() {
	vec4 white = vec4(1.0, 1.0, 1.0, 1.0);
	vec3 L = normalize(light - position);
	vec3 N = normalize(normal);
	vec3 H = normalize(L + (Eye - position));
	float diffuse = dot(N,L);
	float specular;

	if(diffuse < 0.0) {
		diffuse = 0.0;
		specular = 0.0;
	} else {
		specular = pow(max(0.0, dot(N,H)), material.w);
	}

	gl_FragColor = min(material.x*colour + material.y*diffuse*colour +
		material.z*white*specular, vec4(1.0));
	gl_FragColor.a = colour.a;
}
