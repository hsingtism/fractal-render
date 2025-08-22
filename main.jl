using Images, ThreadsX

function coordinateMatrix(center, radiusW, radiusH, widthPixels, heightPixels)
    centerRealPart = real(center)
    centerImagPart = imag(center) * im
    
    realCoords = LinRange(centerRealPart - radiusW, centerRealPart + radiusW, widthPixels)
    imagCoords = LinRange(centerImagPart - radiusH * im, centerImagPart + radiusH * im, heightPixels)

    return realCoords'.+ reverse(imagCoords)
end

function exportImage(mapper, colorer, center = 0.0+0.0im, radiusH = 2,
    heightPixels = 1000, widthPixels = 1000, filename = "image.png")
    
    radiusW = radiusH * widthPixels / heightPixels
    coordinates = coordinateMatrix(center, radiusW, radiusH, widthPixels, heightPixels)
    mappedVals = ThreadsX.map(mapper, coordinates)
    pixelVals = map(colorer, mappedVals)
    save(filename, pixelVals)
end

function normalizedPixelValueBoundry(valueMatrix, biasBright = 1, count = 256 + 1)
    sortedVector = sort(vec(valueMatrix))
    dataLength = length(sortedVector)
    return 1:count .|> x -> (x / count) ^ (1 / biasBright) * dataLength .|> floor .|> Int .|> x -> sortedVector[x]
end

function histogramImage(mapper, colorer, center = 0.0+0.0im, radiusH = 2, brightStretch = 1,
    heightPixels = 1000, widthPixels = 1000, filename = "image.png")
    
    radiusW = radiusH * widthPixels / heightPixels
    coordinates = coordinateMatrix(center, radiusW, radiusH, widthPixels, heightPixels)
    mappedVals = ThreadsX.map(mapper, coordinates)
    
    pixelBoundries = normalizedPixelValueBoundry(mappedVals, brightStretch)
    histogramVals = mappedVals .|> x -> findfirst(v -> v >= x, pixelBoundries) - 1 .|> x -> x / 256

    pixelVals = map(colorer, histogramVals)
    save(filename, pixelVals)
end

