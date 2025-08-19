using Colors, LinearAlgebra

equalHueSpace = rootCount -> v::Tuple -> v[1] == -1 ? HSL(0, 0, 0) : HSL((v[1] - 1) * 360 / rootCount, 1, 0.5)

darkenEdgesEqualHue = (rootCount::Int, inverseDarkenAmount = 5) -> 
    v::Tuple -> v[1] == -1 ? HSL(0, 0, 0) : HSL((v[1] - 1) * 360 / rootCount, 1, max(1 - log(v[2]) / inverseDarkenAmount, 0))

polynomialEvalRoots = (roots, x) -> prod(x .- roots)

function polynomialDerivativeEvalRoots(roots, x)
    deg = length(roots)
    termMatrix = (ones(deg, deg) - I(deg)) .* transpose(x .- roots) + I(deg)
    termMatrixProd = prod.(eachrow(termMatrix))
    return sum(termMatrixProd)
end

rootProximity = (roots, z) -> map(x -> abs(x - z), roots)
closestRoot = (roots, z) -> argmin(rootProximity(roots, z))
closestRootDistance = (roots, z) -> minimum(rootProximity(roots, z))

function newtonIterator(escapeThreshold, roots::Vector, z, dwellLimit)
    for i in 1:dwellLimit
        z = z - polynomialEvalRoots(roots, z) / polynomialDerivativeEvalRoots(roots, z)
        if isnan(z) break end
        if closestRootDistance(roots, z) > escapeThreshold continue end
        return (closestRoot(roots, z), i)
    end

    return (-1, dwellLimit)
end

newtonPolynomial = (roots::Vector, convegenceThreshold = 0.0001, dwellLimit = 1000) -> z::ComplexF64 -> 
    newtonIterator(convegenceThreshold, roots, z, dwellLimit)

rootsOfUnity = n -> map(x -> exp(x / n * 2pi * im), 0:n-1)

mean = vals -> +(vals...) / length(vals)

unstableNewtonMap = (fixedRoots::Vector, convegenceThreshold = 0.0001, dwellLimit = 10000) -> z::ComplexF64 -> 
    newtonIterator(convegenceThreshold, [fixedRoots; z], mean([fixedRoots; z]), dwellLimit)
