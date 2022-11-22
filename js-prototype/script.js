const ctx = document.getElementById('mainp').getContext('2d')

for(let i = 0; i < 600; i++) {
    ctx.fillStyle = (i % 4) ? 'red' : 'black'
    for(let j = 0; j < 600; j++) {
        ctx.fillRect(i,j,1,1)
    }
}