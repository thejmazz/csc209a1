module.exports = function(grunt) {
    grunt.initConfig({
        watch: {
            c: {
                files: ['**/*.c'],
                tasks: ['exec:gcc','exec:remvocals']
            }
        },
 
        exec: {
            gcc: {
                cmd: function() {
                    return 'gcc -Wall -g -o bin/remvocals remvocals.c';
                }
            },
            remvocals : {
               cmd: function() {
                    return './bin/remvocals sdsd sdsd';
                } 
            }
        }
    });
 
    grunt.loadNpmTasks('grunt-exec');
    grunt.loadNpmTasks('grunt-contrib-watch');
    grunt.loadNpmTasks('grunt-open');
 
    grunt.registerTask('compile', ['exec:gcc'])
    grunt.registerTask('run', ['exec:remvocals'])
    grunt.registerTask('default', ['compile', 'watch']);
};
