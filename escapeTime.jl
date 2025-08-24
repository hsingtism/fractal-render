using Colors

linearBlue = maxIter -> v -> HSL(240, 1.0, v / maxIter)
rootBlue = (maxIter, nRoot = 3) -> v -> HSL(240, 1.0, (v / maxIter) ^ (1 / nRoot))
logBlue = maxIter -> v -> HSL(240, 1.0, log(v + 1) / log(maxIter + 1))

chromaBlack = (maxIter, stretch = 300) -> v -> HSL(((v / maxIter) * stretch) * 360, 1.0, v == 0 ? 0 : 0.5)
moduloColor = (colors = 6, offset = 0) -> v -> HSL(360 / colors * (v % colors) + offset, 1.0, v == 0 ? 0 : 0.5) 

histogramBlue = linearBlue(1)

function quadraticLoop(z::ComplexF64, c::ComplexF64, maxIter) 
    for i in 1:maxIter
        z = z * z + c
        if abs(z) > 2
            return i
        end
    end

    return 0
end

mandelbrot = maxIter -> c::ComplexF64 -> quadraticLoop(ComplexF64(0), c, maxIter)
julia = (c::ComplexF64, maxIter) -> z::ComplexF64 -> quadraticLoop(z, c, maxIter)

function freeMandelbrot(z::ComplexF64, c::ComplexF64, p::ComplexF64, maxIter, escapeThreshold::Real)
    for i in 1:maxIter
        z = z ^ p + c
        if abs(z) > escapeThreshold
            return i
        end
    end
    
    return 0
end

weirdMandelbrot = (maxIter, zcpCoefficients, zcpConstants, escapeThreshold::Real = 2) -> screenPos::ComplexF64 -> 
    freeMandelbrot((zcpCoefficients * screenPos + zcpConstants)..., maxIter, escapeThreshold)

