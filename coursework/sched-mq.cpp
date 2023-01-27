/*
 * The Priority Task Scheduler
 * SKELETON IMPLEMENTATION TO BE FILLED IN FOR TASK 1
 */

#include <infos/kernel/sched.h>
#include <infos/kernel/thread.h>
#include <infos/kernel/log.h>
#include <infos/util/list.h>
#include <infos/util/lock.h>

using namespace infos::kernel;
using namespace infos::util;

/**
 * A Multiple Queue priority scheduling algorithm
 */
class MultipleQueuePriorityScheduler : public SchedulingAlgorithm
{
public:
    /**
     * Returns the friendly name of the algorithm, for debugging and selection purposes.
     */
    const char* name() const override { return "mq"; }

    /**
     * Called during scheduler initialisation.
     */
    void init()
    {
        // TODO: Implement me!
    }

    /**
     * Called when a scheduling entity becomes eligible for running.
     * @param entity
     */
    void add_to_runqueue(SchedulingEntity& entity) override
    {
        // TODO: Implement me!
        /* cfs implementation
        UniqueIRQLock l;
		runqueue.enqueue(&entity);
        */

    }

    /**
     * Called when a scheduling entity is no longer eligible for running.
     * @param entity
     */
    void remove_from_runqueue(SchedulingEntity& entity) override
    {
        // TODO: Implement me!
        /*cfs implementation
        UniqueIRQLock l;
		runqueue.remove(&entity);
        */
    }

    /**
     * Called every time a scheduling event occurs, to cause the next eligible entity
     * to be chosen.  The next eligible entity might actually be the same entity, if
     * e.g. its timeslice has not expired.
     */
    SchedulingEntity *pick_next_entity() override
    {
        // TODO: Implement me!
        /* cfs implementation
        if (runqueue.count() == 0) return NULL;
		if (runqueue.count() == 1) return runqueue.first();
		
		SchedulingEntity::EntityRuntime min_runtime = 0;
		SchedulingEntity *min_runtime_entity = NULL;
		for (const auto& entity : runqueue) {
			if (min_runtime_entity == NULL || entity->cpu_runtime() < min_runtime) {
				min_runtime_entity = entity;
				min_runtime = entity->cpu_runtime();
			}
		}
				
		return min_runtime_entity;
        */
    }
};

/* --- DO NOT CHANGE ANYTHING BELOW THIS LINE --- */

RegisterScheduler(MultipleQueuePriorityScheduler);