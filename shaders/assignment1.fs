
#version 130

in vec3 position;

void main() {
	if(position.y <= 0) { // water
		gl_FragColor = vec4(0.1, 0.1, 0.75, 1.0);
	} else if(position.y > 0 && position.y <= 0.7) { // sand
		gl_FragColor = vec4(0.8, 0.7, 0.5, 1.0);
	} else if(position.y > 0.7 && position.y <= 2) { // grass
		gl_FragColor = vec4(0.2, 0.7, 0.2, 1.0);
	} else if(position.y > 2 && position.y <= 3) { // rocks
		gl_FragColor = vec4(0.4, 0.4, 0.4, 1.0);
	} else if(position.y > 3) { // snow
		gl_FragColor = vec4(0.9, 0.9, 0.9, 1.0);
	} else { // default to black
		gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
}
