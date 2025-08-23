# newton fractal with roots of unity
genericMapImage(newtonPolynomial(rootsOfUnity(3)), darkenEdgesEqualHue(3), 0, 0.5)
genericMapImage(newtonPolynomial(rootsOfUnity(5)), darkenEdgesEqualHue(5), 0, 0.5)

# unstable cubic newton map with fixed 2 roots, not zoomed
genericMapImage(unstableNewtonMap([-1, 1]), darkenEdgesEqualHue(3), 0, 2)

# histogram deep mandelbrot rendering
sampleCenter::ComplexF64 =  -1.258968 + 0.034573im
sampleRadiusH::Float64 = 0.00005
histogramImage(mandelbrot(200000), histogramBlue, sampleCenter, sampleRadiusH, 1, 1000, 2000)
genericMapImage(mandelbrot(200000), chromaBlack(200000), sampleCenter, sampleRadiusH, 1000, 2000)

# entire mandelbrot
genericMapImage(mandelbrot(300), rootBlue(300))

# julia set 
genericMapImage(julia(-0.5+0.6im, 500), rootBlue(500))

# weird quadratic maps 
genericMapImage(weirdMandelbrot(200, [0.5, 0.5, 0], [0, 1.15im, 3 + 0.5im], 6), rootBlue(200))
histogramImage(weirdMandelbrot(200, [0.5, 0.5, 0], [0, 1.15im, 3 + 0.5im], 6), histogramBlue)

genericMapImage(weirdMandelbrot(200, [1, 0, 0], [0, 1.15im, 3 + 0.5im], 6), rootBlue(200))
genericMapImage(weirdMandelbrot(200, [1, 0, 0], [0, 1.15im, 3 + 0.5im], 6), chromaBlack(200))
