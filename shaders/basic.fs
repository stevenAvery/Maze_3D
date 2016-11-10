
#version 130

in vec3 position;

void main() {
	//gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);

	float modVal = 100.0;
	float vibrancy = 1/modVal;
	gl_FragColor = vec4(
		mod(position.x, modVal) * vibrancy,
		mod(position.y, modVal) * vibrancy,
		mod(position.z, modVal) * vibrancy, 1.0);
}
