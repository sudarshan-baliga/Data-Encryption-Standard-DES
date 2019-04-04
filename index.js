const { exec } = require("child_process");

const str = "Lorem ipsum dolor sit ametasdf consectetur adipisicing elit. Totam corrupti esse similique et. Perferendis ullam nesciunt soluta dolorum reiciendis repudiandae quasi incidunt architecto eos, illo possimus rem, nostrum sed explicabo ab accusantium! Enim voluptates deserunt nulla assumenda, excepturi culpa exercitationem, minus tempore earum doloribus doloremque sit laborum placeat sint, accusantium itaque? Consequatur ut doloribus optio provident iusto! At perspiciatis, iusto sint deleniti ut deserunt quo architecto, doloribus ab voluptate accusantium maiores vero quidem explicabo inventore laborum aliquid voluptatum, autem dolorem et fuga! Aliquam ullam deserunt rem cupiditate, hic laborum suscipit modi in expedita doloremque. Enim, vero! Totam quis culpa magnam? sadfas adsfas dasfasdfa adsfasdfasdf asdfasdf";
const arr = [];


let len;
for(let i=0;i<str.length;) {
    len = (Math.floor(1+Math.random()*3))*8;
    i += len;
    arr.push(str.slice(i, i+len));
}



let count = 0, ans = 0;


for(let i=0;i<arr.length;++i)
    exec(`./output ${arr[i]} -h -e`, (err, stdout, stderr) => {
        ++count;
        if(count === arr.length) {
            console.log(`Avalance percentage: ${ans/arr.length}`);
            process.exit(0);
        }
        ans += Number.parseFloat(stdout);
    })

