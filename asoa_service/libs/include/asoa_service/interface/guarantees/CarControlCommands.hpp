#include <asoa/core/functionality.hpp>

/*
 * Generated with the ASOA Functionality Generator.
 * Name: CarControlCommands
 * ID: 3722803407959159516
 */

class CarControlCommands: public Functionality
{
  private:
    std::string type_name_ = "ctrlCom";
    uint64_t type_id_ = 3722803407959159516;

  public:
    
    struct Data : public FuncComponentBase
    {
 
		uint8_t frame_counter;
		uint64_t tai_seconds;
		uint32_t tai_nanoseconds;
		float target_vel_x;
		float target_curvature;
		float target_cor_x;
		bool emergency_stop;
 
		bool Data_serialize_topic(ucdrBuffer* writer, const Data* topic)
		{
		    (void) ucdr_serialize_uint8_t(writer, topic->frame_counter);
		
		    (void) ucdr_serialize_uint64_t(writer, topic->tai_seconds);
		
		    (void) ucdr_serialize_uint32_t(writer, topic->tai_nanoseconds);
		
		    (void) ucdr_serialize_float(writer, topic->target_vel_x);
		
		    (void) ucdr_serialize_float(writer, topic->target_curvature);
		
		    (void) ucdr_serialize_float(writer, topic->target_cor_x);
		
		    (void) ucdr_serialize_bool(writer, topic->emergency_stop);
		
		    return !writer->error;
		}
		
		bool Data_deserialize_topic(ucdrBuffer* reader, Data* topic)
		{
		    (void) ucdr_deserialize_uint8_t(reader, &topic->frame_counter);
		
		    (void) ucdr_deserialize_uint64_t(reader, &topic->tai_seconds);
		
		    (void) ucdr_deserialize_uint32_t(reader, &topic->tai_nanoseconds);
		
		    (void) ucdr_deserialize_float(reader, &topic->target_vel_x);
		
		    (void) ucdr_deserialize_float(reader, &topic->target_curvature);
		
		    (void) ucdr_deserialize_float(reader, &topic->target_cor_x);
		
		    (void) ucdr_deserialize_bool(reader, &topic->emergency_stop);
		
		    return !reader->error;
		}
		
		uint32_t Data_size_of_topic(const Data* topic, uint32_t size)
		{
		    uint32_t previousSize = size;
		    size += ucdr_alignment(size, 1) + 1;
		
		    size += ucdr_alignment(size, 8) + 8;
		
		    size += ucdr_alignment(size, 4) + 4;
		
		    size += ucdr_alignment(size, 4) + 4;
		
		    size += ucdr_alignment(size, 4) + 4;
		
		    size += ucdr_alignment(size, 4) + 4;
		
		    size += ucdr_alignment(size, 1) + 1;
		
		    return size - previousSize;
		}
 
        uint32_t maxSize() override
        {
             
            return Data_size_of_topic(this, 0);
             
        }

        bool deserialize(const uint8_t *buffer, uint32_t length) override
        {
             
            ucdrBuffer ucdr_buffer;
            ucdr_init_buffer(&ucdr_buffer, buffer, length);
            return Data_deserialize_topic(&ucdr_buffer, this);
             
        }

        long serialize(uint8_t *buffer, uint32_t max_size) override
        {
             
            ucdrBuffer ucdr_buffer;
            ucdr_init_buffer(&ucdr_buffer, buffer, max_size);
            bool ret = Data_serialize_topic(&ucdr_buffer, this);

            if(!ret){
                return -1;
            }else{
                return ucdr_buffer_length(&ucdr_buffer);
            }
             
        }
    } data_;
 
    struct Quality : public FuncComponentBase
    {
 
		
 

        bool deserialize(const uint8_t *buffer, uint32_t length) override
        {
             
        }

        long serialize(uint8_t *buffer, uint32_t max_size) override
        {
            return 0; 
        }

        virtual uint32_t maxSize() override
        {
            return 0; 
        }

    } quality_;
 
    struct Parameter : public FuncComponentBase
    {
 
		
 
        bool deserialize(const uint8_t *buffer, uint32_t length) override
        {
             
        }

        long serialize(uint8_t *buffer, uint32_t max_size) override
        {
            return 0; 
        }

        virtual uint32_t maxSize() override
        {
            return 0; 
        }

    } parameter_;

    void Functionality()
    {
    }

    const std::string &getTypeName() override
    {
        return type_name_;
    }

    std::uint32_t getTypeID() override
    {
        return type_id_;
    }
};