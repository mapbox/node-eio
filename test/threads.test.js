var eio = require('..');
var assert = require('assert');

describe('threads', function() {
    it('should allow setting the min number of threads', function() {
        // Increase number of threads to 1.5x the number of logical CPUs.
        var cpus = require('os').cpus().length;
        var threads = Math.ceil(Math.max(4, cpus* 1.5));
        eio.setMinParallel(threads);
    });

    it('should allow setting the max number of threads', function() {
        // Increase number of threads to 1.5x the number of logical CPUs.
        var cpus = require('os').cpus().length;
        var threads = Math.ceil(Math.max(4, cpus* 1.5));
        eio.setMaxParallel(threads);
    });

    it('should allow access to usage', function() {
        var ver = process.versions.node;
        if (parseInt(ver.split('.')[1],10) < 9) {
            assert.ok(eio.usage().requests !== undefined);
            assert.ok(eio.usage().active !== undefined);
            assert.ok(eio.usage().pending !== undefined);
        } else {
            console.warn('note: your node version does not support eio so this test is disabled');
        }
    });
});
