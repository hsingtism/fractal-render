const variableVariable = 1 // 1 is julia (changing seed), 0 is fatou (changing function)
// const constantValue = [0, 0]
const constantValue = [0.262, 0.454]
const iteratorFunction = (z, c) => addComplex(squareComplex(z), c)

const ctx = document.getElementById('mainp').getContext('2d')
const addComplex = (a, b) => [a[0] + b[0], a[1] + b[1]]
const squareComplex = (a) => [a[0] * a[0] - a[1] * a[1], 2 * a[0] * a[1]]
const absComplex = (a) => Math.sqrt(a[0] * a[0] + a[1] * a[1])

function drawPixel(x, y, color) {
    ctx.fillStyle = color
    ctx.fillRect(x, y, 1, 1)
}

for(let i = 0; i < 600; i++) {
    for(let j = 0; j < 600; j++) {
        let re = -2 + i / 150
        let im = -2 + j / 150
        let color = classicJ([re, im])
        drawPixel(i, j, color)
    }
}


function classicJ(x) {
    let c = variableVariable ? constantValue : x
    let z = variableVariable ? x : constantValue

    for (let i = 0; i < 10000; i++) {
        let zf = z
        z = iteratorFunction(z, c)
        if (absComplex(z) > 1000) {
            return 'gray'
        }
        if (zf[0] == z[0] && zf[1] == z[1]) {
            return 'black'
        }
    }
    return 'black'
}
