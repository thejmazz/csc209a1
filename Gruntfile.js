module.exports = function(grunt) {
    grunt.initConfig({
        watch: {
            c: {
                files: ['**/*.c'],
                tasks: ['exec:gcc','exec:run']
            }
        },
 
        exec: {
            gcc: {
                cmd: function() {
                    //return 'gcc -Wall -g -o bin/remvocals remvocals.c';
                    return 'gcc -Wall -g -o bin/addecho addecho.c';
                }
            },
            run : {
               cmd: function() {
                    //return './bin/remvocals src-audio/love.wav output/love-no-vocals.wav';
                    return './bin/addecho -d 3 -v 2 src-audio/short.wav output/short-echo.wav';
                } 
            }
        }
    });
 
    grunt.loadNpmTasks('grunt-exec');
    grunt.loadNpmTasks('grunt-contrib-watch');
    grunt.loadNpmTasks('grunt-open');
 
    grunt.registerTask('compile', ['exec:gcc'])
    grunt.registerTask('run', ['exec:run'])
    grunt.registerTask('default', ['compile','run', 'watch']);
};
