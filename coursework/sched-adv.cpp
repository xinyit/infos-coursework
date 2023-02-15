/*
 * The Advanced Priority Task Scheduler
 */

#include <infos/kernel/sched.h>
#include <infos/kernel/thread.h>
#include <infos/kernel/log.h>
#include <infos/util/list.h>
#include <infos/util/lock.h>
#include <infos/kernel/sched-entity.h>

using namespace infos::kernel;
using namespace infos::util;

/**
 * A Multiple Queue priority scheduling algorithm
 */
class AdvancedMultipleQueuePriorityScheduler : public SchedulingAlgorithm
{
public:
    /**
     * Returns the friendly name of the algorithm, for debugging and selection purposes.
     */
    const char* name() const override { return "adv"; }

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

       UniqueIRQLock l;

       SchedulingEntityPriority::SchedulingEntityPriority p;

       p = entity.priority();

       switch(p) {
            case SchedulingEntityPriority::REALTIME:
                realTimeQueue.enqueue(&entity);
                break;
            case SchedulingEntityPriority::INTERACTIVE:
                interactiveQueue.enqueue(&entity);
                break;
            case SchedulingEntityPriority::NORMAL:
                normalQueue.enqueue(&entity);
                break;
            case SchedulingEntityPriority::DAEMON:
                daemonQueue.enqueue(&entity);
                break;
       }

    }

    /**
     * Called when a scheduling entity is no longer eligible for running.
     * @param entity
     */
    void remove_from_runqueue(SchedulingEntity& entity) override
    {

        UniqueIRQLock l;

        SchedulingEntityPriority::SchedulingEntityPriority p;

        p = entity.priority();

        switch(p) {
                case SchedulingEntityPriority::REALTIME:
                    realTimeQueue.remove(&entity);
                    break;
                case SchedulingEntityPriority::INTERACTIVE:
                    interactiveQueue.remove(&entity);
                    break;
                case SchedulingEntityPriority::NORMAL:
                    normalQueue.remove(&entity);
                    break;
                case SchedulingEntityPriority::DAEMON:
                    daemonQueue.remove(&entity);
                    break;
       }
    }

    /**
     * Called every time a scheduling event occurs, to cause the next eligible entity
     * to be chosen.  The next eligible entity might actually be the same entity, if
     * e.g. its timeslice has not expired.
     */
    SchedulingEntity *pick_next_entity() override
    {
        SchedulingEntity* nextInQueue;
        
        if (realTimeQueue.count()==0 && interactiveQueue.count()==0 && normalQueue.count()==0 && daemonQueue.count()==0) return NULL;

        if(!realTimeQueue.count()==0) 
        {
            nextInQueue = realTimeQueue.first();
            interactiveQueue.append(realTimeQueue.dequeue());
           
        } else if (!interactiveQueue.count()==0)
        {
            nextInQueue = interactiveQueue.first();
            normalQueue.append(interactiveQueue.dequeue());
        } else if (!normalQueue.count()==0)
        {
            nextInQueue = normalQueue.first();
            daemonQueue.append(normalQueue.dequeue());
        } else {
             nextInQueue = daemonQueue.first();
             daemonQueue.append(normalQueue.dequeue());
        }
        return nextInQueue;
       
    }

private:
	List<SchedulingEntity *> realTimeQueue;
    List<SchedulingEntity *> interactiveQueue;
    List<SchedulingEntity *> normalQueue;
    List<SchedulingEntity *> daemonQueue;

};

/* --- DO NOT CHANGE ANYTHING BELOW THIS LINE --- */

RegisterScheduler(AdvancedMultipleQueuePriorityScheduler);