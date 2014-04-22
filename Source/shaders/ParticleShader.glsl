// Copyright 2014 The Ephenation Authors
//
// This file is part of Ephenation.
//
// Ephenation is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.
//
// Ephenation is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Ephenation.  If not, see <http://www.gnu.org/licenses/>.

-- Vertex

// Take an 8-bit signed number and convert it to a texture bitmap offset
float ConvertIntToTexture(int n) {
	if (n < 128)
		return float(n)/TEXTURESCALING;
	else
		return float(n-256)/TEXTURESCALING;
}

uniform mat4 modelMatrix;
// This contains both a offset and a multiplier to be used for the bitmap. It enables the use
// of atlas bitmaps.
uniform vec3 textOffsMulti = vec3(0,0,1);
in vec4 normal;
in vec4 vertex; // First 3 are vertex coordinates, the 4:th is texture data coded as two scaled bytes
in int material;
out vec3 fragmentNormal;
out vec2 fragmentTexCoord;
out float extIntensity;
out float extAmbientLight;
out vec3 position;
out float materialEffectDensity;
flat out int materialEffectType;
void main(void)
{
	mat4 newModelMatrix = modelMatrix;
	float dx, dy, dz;
	if (0) {
		dx = snoise(vec2(gl_InstanceID/1.1234, UBOTime/10.0))*5.0;
		dy = snoise(vec2(gl_InstanceID/1.6331, UBOTime/10.0))*5.0;
		dz = snoise(vec2(gl_InstanceID/1.3451, UBOTime/10.0))*5.0;
	} else {
		dx = snoise(vec2(gl_InstanceID/40.0+UBOTime/5.0, 0.0))*10.0;
		dy = snoise(vec2(gl_InstanceID/45.0+UBOTime/5.0, 0.0))*10.0;
		dz = snoise(vec2(gl_InstanceID/50.0+UBOTime/5.0, 0.0))*10.0;
	}
	newModelMatrix[3] += vec4(dx, dy, dz, 0.0);
	vec4 vertexScaled = vec4(vec3(vertex) / VERTEXSCALING, 1);
	int t1 = int(vertex[3]); // Extract the texture data
	vec2 textureScaled = vec2(ConvertIntToTexture(t1&0xFF), ConvertIntToTexture(t1>>8));
	int intens2 = int(normal[3]); // Bit 0 to 3 is sun intensity, 4 to 7 is ambient light
	if (intens2 < 0) intens2 += 256;
	float textMult = textOffsMulti.z;
	fragmentTexCoord = textureScaled*textMult + textOffsMulti.xy;
	fragmentNormal = normalize((newModelMatrix*vec4(normal.xyz/NORMALSCALING, 0.0)).xyz);
	gl_Position = UBOProjectionviewMatrix * newModelMatrix * vertexScaled;
	position = vec3(newModelMatrix * vertexScaled); // Copy position to the fragment shader
	// Scale the intensity from [0..255] to [0..1].
	extIntensity = (intens2 & 0x0F)/15.0;
	// "	extIntensity = 0.1;
	extAmbientLight = (intens2 >> 4)/15.0;
	// "   extAmbientLight = 1;
	materialEffectDensity = 0;
	materialEffectType = material;
}

-- Fragment

uniform sampler2D firstTexture;
in vec3 fragmentNormal;
in vec2 fragmentTexCoord;
in float extIntensity;
in float extAmbientLight;
in vec3 position;       // The model coordinate, as given by the vertex shader
in float materialEffectDensity;
flat in int materialEffectType;
layout(location = 0) out vec4 diffuseOutput;
layout(location = 1) out vec4 posOutput;
layout(location = 2) out vec4 normOutput;
layout(location = 3) out int materialOutput;
void main(void)
{
	if (distance(UBOCamera.xyz, position) > UBOViewingDistance) { discard; return; }
	vec4 clr = texture(firstTexture, fract(fragmentTexCoord));
	float alpha = clr.a;
	if (alpha == 0) { discard; return; }               // For some reason, some alpha that should be discarded is still not exactly 0.
	posOutput.xyz = position;                            // This position shall not be transformed by the view matrix
	posOutput.a = extIntensity;                          // Use the alpha channel for sun intensity. TODO: This is a 32-bit float, very inefficient
	normOutput = vec4(fragmentNormal, extAmbientLight); // Use alpha channel of normal for ambient info.
	diffuseOutput = clr;
	materialOutput = ((int(materialEffectDensity*15.0) << 4) + materialEffectType);
}
