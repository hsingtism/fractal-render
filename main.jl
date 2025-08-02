using Images, ThreadsX

function coordinateMatrix(center, radiusW, radiusH, widthPixels, heightPixels)
    centerRealPart = real(center)
    centerImagPart = imag(center) * im
    
    realCoords = LinRange(centerRealPart - radiusW, centerRealPart + radiusW, widthPixels)
    imagCoords = LinRange(centerImagPart - radiusH * im, centerImagPart + radiusH * im, heightPixels)

    return realCoords'.+ reverse(imagCoords)
end

function exportImage(mapper, colorer, center, radiusH, heightPixels, widthPixels)
    radiusW = radiusH * widthPixels / heightPixels
    coordinates = coordinateMatrix(center, radiusW, radiusH, widthPixels, heightPixels)
    mappedVals = ThreadsX.map(mapper, coordinates)

    # blackPoint = minimum(filter(x -> x != 0, mappedVals))
    pixelVals = map(colorer, mappedVals)
    save("image.png", pixelVals)
end
