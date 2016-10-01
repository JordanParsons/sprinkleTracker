
uniform sampler2DRect tex;
uniform float max_radius;

void main(void) {
    
    vec4 finalColor = vec4(0.0,0.0,0.0,1.0);
    float weight = 0.;//vec4(0.,0.,0.,0.);
    int radius = int(max_radius);
    for(int x=radius*-1;x<radius;x++) {
        for(int y=radius*-1;y<radius;y++){
            vec2 coord = gl_TexCoord[0].xy+vec2(x,y);
            if(distance(coord, gl_TexCoord[0].xy) < float(radius)){
                vec4 texel = texture2DRect(tex, coord);
                float w = length(texel.rgb)+0.1;
                weight+=w;
                finalColor += texel*w;
            }
        }
    }
    
    gl_FragColor = finalColor/weight;
}
/*
uniform sampler2D baseImage;
uniform float brightPassThreshold;

void main(void) {
    vec3 luminanceVector = vec3(0.2125, 0.7154, 0.0721);
    vec4 sample = texture2D(baseImage, gl_TexCoord[0].st);
    
    float luminance = dot(luminanceVector, sample.rgb);
    luminance = max(0.0, luminance - brightPassThreshold);
    sample.rgb *= sign(luminance);
    sample.a = 1.0;
    
    gl_FragColor = sample;
}*/