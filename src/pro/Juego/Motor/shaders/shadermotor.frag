uniform vec2 userCoor;
uniform sampler2D texture;
uniform float radius;

void main() {
    float dist = distance(gl_FragCoord.xy, userCoor);
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    float alpha = (dist > radius)? 0.0: pixel.a;
    gl_FragColor = gl_Color * pixel;
    gl_FragColor.a = alpha;
}