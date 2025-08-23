using Images, ThreadsX, Colors

function buddhabrotSampleMap(c::ComplexF64, maxIter)
    z = ComplexF64(0)
    visitedPoints = ComplexF64[]

    for i in 1:maxIter
        z = z * z + c
        if abs(real(z)) > 2 || abs(imag(z)) > 2
            return visitedPoints
        end
        if abs(z) > 2
            push!(visitedPoints, z)
            return visitedPoints
        end
        push!(visitedPoints, z)
    end

    return ComplexF64[] # does not escape, in the set
end

function antibuddhabrotSampleMap(c::ComplexF64, maxIter)
    z = ComplexF64(0)
    visitedPoints = ComplexF64[]

    for i in 1:maxIter
        z = z * z + c
        if abs(z) > 2
            return ComplexF64[]
        end
        push!(visitedPoints, z)
    end

    return visitedPoints
end

function buddhabrot(maxIterations, additionalPointFactor = 1, center = 0.0+0.0im, radiusH = 2,
    heightPixels = 1000, widthPixels = 1000,  
    filename = "antibuddhabrot.png")

    radiusW = radiusH * widthPixels / heightPixels
    
    coordinatesSampleMatrix = coordinateMatrix(center, radiusW, radiusH, widthPixels * additionalPointFactor, heightPixels * additionalPointFactor)
    coordinatesSampleVec = vec(coordinatesSampleMatrix)
    visitedValuesMatrix = ThreadsX.map(x -> buddhabrotSampleMap(x, maxIterations), coordinatesSampleVec)
    visitedValues = visitedValuesMatrix |> Iterators.flatten |> collect
    # TODO prevent too much memory use
    
    coordinatesImage = coordinateMatrix(center, radiusW, radiusH, widthPixels, heightPixels)
    imageCoordReal = coordinatesImage[1, :] .|> real
    imageCoordImag = coordinatesImage[:, 1] .|> imag
    incrementIndex = visitedValues .|> visited -> [findfirst(t -> t <= imag(visited), imageCoordImag), findfirst(t -> t >= real(visited), imageCoordReal)]

    pixelVals = coordinatesImage .|> x -> 0
    incrementIndex .|> v -> pixelVals[v...] += 1 # ! mutation

    maxBucket = maximum(pixelVals)
    pixelVals = map(x -> HSL(180, 0.5, x / maxBucket), pixelVals) # ! mutation
    save(filename, pixelVals)

end