using Colors

linearBlue = maxIter -> v -> HSL(240, 1.0, v / maxIter)
rootBlue = maxIter -> v -> HSL(240, 1.0, (v / maxIter) ^ (1 / 3))
rootBlueBlackPoint = maxIter -> blackPoint -> v -> HSL(240, 0, (max(v - blackPoint, 0) / (maxIter - blackPoint)) ^ (1 / 15))
chromaBlack = maxIter -> v -> HSL(((v / maxIter) * 500) * 360 % 360, 1.0, v == 0 ? 0 : 0.5)

# interesting region in Mandelbrot for testing
center::ComplexF64 =  -1.258968 + 0.034573im
radiusH::Float64 = 0.00005

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
julia = (maxIter, c::ComplexF64) -> z::ComplexF64 -> quadraticLoop(z, c, maxIter)

function freeMandelbrot(z::ComplexF64, c::ComplexF64, p::ComplexF64, maxIter)

    println(maxIter)
    println(z)
    println(c)
    println(p)
    return

    for i in 1:maxIter
        z = z ^ p + c
        if abs(z) > 2
            return i
        end
    end
    
    return 0
end

## ! untested
weirdMandelbrot = (maxIter, zcpCoefficients, zcpConstants) -> screenPos::ComplexF64 -> 
    freeMandelbrot((zcpCoefficients * screenPos + zcpConstants)..., maxIter)

