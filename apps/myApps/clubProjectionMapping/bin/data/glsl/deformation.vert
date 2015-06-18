uniform vec2 leftTop;
uniform vec2 rightTop;
uniform vec2 rightBottom;
uniform vec2 leftBottom;

uniform vec2 movieSize;

vec2 deform(vec2 v, vec2 a, vec2 b, vec2 c, vec2 d){
    float x_ratio = v.x/movieSize.x;
    float y_ratio = v.y/movieSize.y;
    
    return vec4(a + x_ratio * (1-y_ratio) * b + x_ratio * y_ratio * c + (1-x_ratio) * y_ratio * d, 0.0, 0.0);
}

void main(){
//    gl_TexCoord[0] = gl_TextureMatrix[0];
    gl_TexCoord[0] = gl_MultiTexCoord0;
    
    vec2 b = rightTop - leftTop;
    vec2 c = rightBottom - leftTop;
    vec2 d = leftBottom - leftTop;
    
    gl_Position = deform(gl_Vertex, leftTop, b, c, d);
    gl_FrontColor = gl_Color;
}