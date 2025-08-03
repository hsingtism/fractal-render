using Colors, LinearAlgebra

equalHueSpace = rootCount -> rootNumber -> HSL((rootNumber - 1) * 360 / rootCount, 1, 0.5)

polynomialEvalRoots = (roots, x) -> prod(x .- roots)

function polynomialDerivativeEvalRoots(roots, x)
    deg = length(roots)
    termMatrix = (ones(deg, deg) - I(deg)) .* (x .- roots) + I(deg)
    termMatrixProd = prod.(eachrow(termMatrix))
    return sum(termMatrixProd)
end

rootProximity = (roots, z) -> map(x -> abs(x - z), roots)
closestRoot = (roots, z) -> argmin(rootProximity(roots, z))[2]
closestRootDistance = (roots, z) -> minimum(rootProximity(roots, z))

function newtonIterator(escapeThreshold, roots, z)
    while true
        z = z - polynomialEvalRoots(roots, z) / polynomialDerivativeEvalRoots(roots, z)
        if closestRootDistance(roots, z) > escapeThreshold continue end
        return closestRoot(roots, z)
    end
    # return 0
end

newtonPolynomial = (convegenceThreshold, roots) -> z::ComplexF64 -> newtonIterator(convegenceThreshold, roots, z)
