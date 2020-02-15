#version 140
out vec4 fragmentColor;
in vec2 out_uv;

uniform sampler2D textureSampler;

void main() {
	//fragmentColor = vec4(1.0, 1.0, 1.0, 1.0);
	fragmentColor = texture(textureSampler, out_uv).rgba;
}