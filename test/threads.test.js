var eio = require('..');

describe('threads', function() {
    it('should allow setting the number of threads', function() {
        // Increase number of threads to 1.5x the number of logical CPUs.
        var cpus = require('os').cpus().length;
        var threads = Math.ceil(Math.max(4, cpus* 1.5));
        eio.setMinParallel(threads);
    });
});
