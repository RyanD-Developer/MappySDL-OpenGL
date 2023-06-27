#version 330 core

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 scaleMatrix;
uniform mat4 rotateMatrix;
uniform mat4 translateMatrix;
uniform mat4 proj;

void main()
{
    vec4 v1 =  translateMatrix * rotateMatrix *  scaleMatrix * vec4(vertexPosition.xy, 0.0, 1.0);
    vec4 v2 = proj * v1;

    gl_Position = v2;

    fragmentColor = vertexColor;
    fragmentUV = vertexUV;

    //if (flip == 1)
        //fragmentUV = vec2(vertexUV.x, flip - vertexUV.y);
}
