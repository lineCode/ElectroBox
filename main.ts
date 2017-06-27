declare function requestNextTick(fn:Function):number;

requestAnimationFrame(()=>{

});

let counter = 0;

let loop = () => {
    requestNextTick(loop);
};

requestNextTick(loop);
