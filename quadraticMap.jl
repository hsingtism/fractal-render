# center::ComplexF64 =  -1.258968 + 0.034575im
center::ComplexF64 =  -1.258968 + 0.034573im
radiusH::Float64 = 0.00005

function mandelbrotLoop(c::ComplexF64, maxIter) 
    z::ComplexF64 = 0

    for i in 1:maxIter #magic num
        z = z * z + c
        if abs(z) > 2
            return i
        end
    end

    return 0
end

mandelbrotMap = maxIter -> c::ComplexF64 -> mandelbrotLoop(c, maxIter)
