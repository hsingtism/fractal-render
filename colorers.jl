using Colors

linearBlue = maxIter -> v -> HSL(240, 1.0, v / maxIter)
rootBlue = maxIter -> blackPoint -> v -> HSL(240, 0, (max(v - blackPoint, 0) / (maxIter - blackPoint)) ^ (1 / 15))
chromaBlack = maxIter -> v -> HSL(((v / maxIter) * 500) * 360 % 360, 1.0, v == 0 ? 0 : 0.5)
