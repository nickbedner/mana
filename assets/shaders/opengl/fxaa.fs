#version 410

in vec2 vTexCoord;
layout(location = 0) out vec4 fragColor;

uniform sampler2D uColorTexture;

uniform vec2 uTexelStep;
uniform int uShowEdges;
uniform int uFXAAOn;

uniform float uLumaThreshold;
uniform float uMulReduce;
uniform float uMinReduce;
uniform float uMaxSpan;

// see FXAA
// http://developer.download.nvidia.com/assets/gamedev/files/sdk/11/FXAA_WhitePaper.pdf
// http://iryoku.com/aacourse/downloads/09-FXAA-3.11-in-15-Slides.pdf
// http://horde3d.org/wiki/index.php5?title=Shading_Technique_-_FXAA

void main(void)
{
    vec3 rgbM = texture(uColorTexture, vTexCoord).rgb;

	// Possibility to toggle FXAA on and off.
	if (uFXAAOn == 0)
	{
		fragColor = vec4(rgbM, 1.0);

		return;
	}

	// Sampling neighbour texels. Offsets are adapted to OpenGL texture coordinates.
	vec3 rgbNW = textureOffset(uColorTexture, vTexCoord, ivec2(-1, 1)).rgb;
    vec3 rgbNE = textureOffset(uColorTexture, vTexCoord, ivec2(1, 1)).rgb;
    vec3 rgbSW = textureOffset(uColorTexture, vTexCoord, ivec2(-1, -1)).rgb;
    vec3 rgbSE = textureOffset(uColorTexture, vTexCoord, ivec2(1, -1)).rgb;

	// see http://en.wikipedia.org/wiki/Grayscale
	const vec3 toLuma = vec3(0.299, 0.587, 0.114);

	// Convert from RGB to luma.
	float lumaNW = dot(rgbNW, toLuma);
	float lumaNE = dot(rgbNE, toLuma);
	float lumaSW = dot(rgbSW, toLuma);
	float lumaSE = dot(rgbSE, toLuma);
	float lumaM = dot(rgbM, toLuma);

	// Gather minimum and maximum luma.
	float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
	float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));

	// If contrast is lower than a maximum threshold ...
	if (lumaMax - lumaMin < lumaMax * uLumaThreshold)
	{
		// ... do no AA and return.
		fragColor = vec4(rgbM, 1.0);

		return;
	}

	// Sampling is done along the gradient.
	vec2 samplingDirection;
	samplingDirection.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
    samplingDirection.y =  ((lumaNW + lumaSW) - (lumaNE + lumaSE));

    // Sampling step distance depends on the luma: The brighter the sampled texels, the smaller the final sampling step direction.
    // This results, that brighter areas are less blurred/more sharper than dark areas.
    float samplingDirectionReduce = max((lumaNW + lumaNE + lumaSW + lumaSE) * 0.25 * uMulReduce, uMinReduce);

	// Factor for norming the sampling direction plus adding the brightness influence.
	float minSamplingDirectionFactor = 1.0 / (min(abs(samplingDirection.x), abs(samplingDirection.y)) + samplingDirectionReduce);

    // Calculate final sampling direction vector by reducing, clamping to a range and finally adapting to the texture size.
    samplingDirection = clamp(samplingDirection * minSamplingDirectionFactor, vec2(-uMaxSpan, -uMaxSpan), vec2(uMaxSpan, uMaxSpan)) * uTexelStep;

	// Inner samples on the tab.
	vec3 rgbSampleNeg = texture(uColorTexture, vTexCoord + samplingDirection * (1.0/3.0 - 0.5)).rgb;
	vec3 rgbSamplePos = texture(uColorTexture, vTexCoord + samplingDirection * (2.0/3.0 - 0.5)).rgb;

	vec3 rgbTwoTab = (rgbSamplePos + rgbSampleNeg) * 0.5;

	// Outer samples on the tab.
	vec3 rgbSampleNegOuter = texture(uColorTexture, vTexCoord + samplingDirection * (0.0/3.0 - 0.5)).rgb;
	vec3 rgbSamplePosOuter = texture(uColorTexture, vTexCoord + samplingDirection * (3.0/3.0 - 0.5)).rgb;

	vec3 rgbFourTab = (rgbSamplePosOuter + rgbSampleNegOuter) * 0.25 + rgbTwoTab * 0.5;

	// Calculate luma for checking against the minimum and maximum value.
	float lumaFourTab = dot(rgbFourTab, toLuma);

	// Are outer samples of the tab beyond the edge ...
	if (lumaFourTab < lumaMin || lumaFourTab > lumaMax)
	{
		// ... yes, so use only two samples.
		fragColor = vec4(rgbTwoTab, 1.0);
	}
	else
	{
		// ... no, so use four samples.
		fragColor = vec4(rgbFourTab, 1.0);
	}

	// Show edges for debug purposes.
	if (uShowEdges != 0)
	{
		fragColor.r = 1.0;
	}
}