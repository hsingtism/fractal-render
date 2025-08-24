using Images, ThreadsX, Colors

complexRectangularBetween = (lo, hi) -> x -> real(lo) <= real(x) <= real(hi) && imag(lo) <= imag(x) <= imag(hi) 

function buddhabrotSampleMap(c::ComplexF64, maxIter)
    z = ComplexF64(0)
    visitedPoints = ComplexF64[]

    for i in 1:maxIter
        z = z * z + c
        push!(visitedPoints, z)
        if abs(z) > 2
            return visitedPoints
        end
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

function evalulateSamples(samples, sampleMap::Function, maxIter, pixelCoordinates::Matrix{ComplexF64})
    visitedValuesAll = map(x -> sampleMap(x, maxIter), samples) |> Iterators.flatten |> collect
    visitedValues = filter(complexRectangularBetween(pixelCoordinates[end, 1], pixelCoordinates[1, end]), visitedValuesAll)
    
    imageCoordReal = pixelCoordinates[1, :] .|> real
    imageCoordImag = pixelCoordinates[:, 1] .|> imag
    incrementIndex = visitedValues .|> visited -> [findfirst(t -> t <= imag(visited), imageCoordImag), findfirst(t -> t >= real(visited), imageCoordReal)]

    pixelVals = pixelCoordinates .|> x -> 0
    incrementIndex .|> v -> pixelVals[v...] += 1 # ! mutation

    return pixelVals
end

function buddhabrot(maxIterations, sampleGridSide = 1000, pixelsPerBatch = 22000, center = 0.0+0.0im, radiusH = 2,
    mapper = buddhabrotSampleMap, colorer = logBlue, heightPixels = 1000, widthPixels = 1000, filename = "buddhabrot.png")

    radiusW = radiusH * widthPixels / heightPixels
    
    coordinatesSampleVec = coordinateMatrix(ComplexF64(0), 2, 2, sampleGridSide, sampleGridSide) |> vec
    coordinatesSamplePadded = [coordinatesSampleVec; fill(NaN + 0.0im, pixelsPerBatch - length(coordinatesSampleVec) % pixelsPerBatch)]
    coordinatesSampleWrapped = reshape(coordinatesSamplePadded, Int(length(coordinatesSamplePadded) / pixelsPerBatch), pixelsPerBatch)
    
    coordinatesImage = coordinateMatrix(center, radiusW, radiusH, widthPixels, heightPixels)
    
    global lastMappedValues = mappedVals = ThreadsX.sum(evalulateSamples(batchSample, mapper, maxIterations, coordinatesImage) 
        for batchSample in eachrow(coordinatesSampleWrapped))

    adaptedColorer = mappedVals |> maximum |> colorer
    pixelVals = map(adaptedColorer, mappedVals)
    save(filename, pixelVals)

end
