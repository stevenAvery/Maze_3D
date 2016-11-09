
#version 130

in vec3 normal;
in vec3 position;
uniform vec3 light;

void main() {
	//vec3 L = normalize(light - position);
	vec3 N = normalize(normal);

	gl_FragColor = vec4(N, 1.0);
}
