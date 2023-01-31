#include <asoa/core/functionality.hpp>

/*
 * Generated with the ASOA Functionality Generator.
 * Name: dyn_state
 * ID: 2266472067984728733
 */

class dyn_state: public Functionality
{
  private:
    std::string type_name_ = "dyn_state";
    uint64_t type_id_ = 2266472067984728733;

  public:
    
    struct Data : public FuncComponentBase
    {
 
		uint8_t frame_counter;
		uint64_t tai_seconds;
		uint32_t tai_nanoseconds;
		float drive_torque_Nm;
		float drive_speed_rad_s;
		float continuous_drive_torque_Nm;
		float max_drive_torque_Nm;
		float max_brake_torque_Nm;
		float brake_torque_Nm;
		float max_regen_brake_torque_Nm;
		float steering_torque_nm;
		float steering_angle_rad;
		float max_steering_angle_velocity_rad_s;
		bool parking_brake_active;
 
		bool Data_serialize_topic(ucdrBuffer* writer, const Data* topic)
		{
		    (void) ucdr_serialize_uint8_t(writer, topic->frame_counter);
		
		    (void) ucdr_serialize_uint64_t(writer, topic->tai_seconds);
		
		    (void) ucdr_serialize_uint32_t(writer, topic->tai_nanoseconds);
		
		    (void) ucdr_serialize_float(writer, topic->drive_torque_Nm);
		
		    (void) ucdr_serialize_float(writer, topic->drive_speed_rad_s);
		
		    (void) ucdr_serialize_float(writer, topic->continuous_drive_torque_Nm);
		
		    (void) ucdr_serialize_float(writer, topic->max_drive_torque_Nm);
		
		    (void) ucdr_serialize_float(writer, topic->max_brake_torque_Nm);
		
		    (void) ucdr_serialize_float(writer, topic->brake_torque_Nm);
		
		    (void) ucdr_serialize_float(writer, topic->max_regen_brake_torque_Nm);
		
		    (void) ucdr_serialize_float(writer, topic->steering_torque_nm);
		
		    (void) ucdr_serialize_float(writer, topic->steering_angle_rad);
		
		    (void) ucdr_serialize_float(writer, topic->max_steering_angle_velocity_rad_s);
		
		    (void) ucdr_serialize_bool(writer, topic->parking_brake_active);
		
		    return !writer->error;
		}
		
		bool Data_deserialize_topic(ucdrBuffer* reader, Data* topic)
		{
		    (void) ucdr_deserialize_uint8_t(reader, &topic->frame_counter);
		
		    (void) ucdr_deserialize_uint64_t(reader, &topic->tai_seconds);
		
		    (void) ucdr_deserialize_uint32_t(reader, &topic->tai_nanoseconds);
		
		    (void) ucdr_deserialize_float(reader, &topic->drive_torque_Nm);
		
		    (void) ucdr_deserialize_float(reader, &topic->drive_speed_rad_s);
		
		    (void) ucdr_deserialize_float(reader, &topic->continuous_drive_torque_Nm);
		
		    (void) ucdr_deserialize_float(reader, &topic->max_drive_torque_Nm);
		
		    (void) ucdr_deserialize_float(reader, &topic->max_brake_torque_Nm);
		
		    (void) ucdr_deserialize_float(reader, &topic->brake_torque_Nm);
		
		    (void) ucdr_deserialize_float(reader, &topic->max_regen_brake_torque_Nm);
		
		    (void) ucdr_deserialize_float(reader, &topic->steering_torque_nm);
		
		    (void) ucdr_deserialize_float(reader, &topic->steering_angle_rad);
		
		    (void) ucdr_deserialize_float(reader, &topic->max_steering_angle_velocity_rad_s);
		
		    (void) ucdr_deserialize_bool(reader, &topic->parking_brake_active);
		
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
		
		    size += ucdr_alignment(size, 4) + 4;
		
		    size += ucdr_alignment(size, 4) + 4;
		
		    size += ucdr_alignment(size, 4) + 4;
		
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
 
		uint8_t frame_counter;
		uint64_t tai_seconds;
		uint32_t tai_nanoseconds;
		uint8_t dynamicsmodul_status_bitmask;
		uint8_t drive_status_bitmask;
		uint8_t brake_status_bitmask;
		uint8_t steering_status_bitmask;
		uint8_t parkingbrake_status_bitmask;
 
		bool Quality_serialize_topic(ucdrBuffer* writer, const Quality* topic)
		{
		    (void) ucdr_serialize_uint8_t(writer, topic->frame_counter);
		
		    (void) ucdr_serialize_uint64_t(writer, topic->tai_seconds);
		
		    (void) ucdr_serialize_uint32_t(writer, topic->tai_nanoseconds);
		
		    (void) ucdr_serialize_uint8_t(writer, topic->dynamicsmodul_status_bitmask);
		
		    (void) ucdr_serialize_uint8_t(writer, topic->drive_status_bitmask);
		
		    (void) ucdr_serialize_uint8_t(writer, topic->brake_status_bitmask);
		
		    (void) ucdr_serialize_uint8_t(writer, topic->steering_status_bitmask);
		
		    (void) ucdr_serialize_uint8_t(writer, topic->parkingbrake_status_bitmask);
		
		    return !writer->error;
		}
		
		bool Quality_deserialize_topic(ucdrBuffer* reader, Quality* topic)
		{
		    (void) ucdr_deserialize_uint8_t(reader, &topic->frame_counter);
		
		    (void) ucdr_deserialize_uint64_t(reader, &topic->tai_seconds);
		
		    (void) ucdr_deserialize_uint32_t(reader, &topic->tai_nanoseconds);
		
		    (void) ucdr_deserialize_uint8_t(reader, &topic->dynamicsmodul_status_bitmask);
		
		    (void) ucdr_deserialize_uint8_t(reader, &topic->drive_status_bitmask);
		
		    (void) ucdr_deserialize_uint8_t(reader, &topic->brake_status_bitmask);
		
		    (void) ucdr_deserialize_uint8_t(reader, &topic->steering_status_bitmask);
		
		    (void) ucdr_deserialize_uint8_t(reader, &topic->parkingbrake_status_bitmask);
		
		    return !reader->error;
		}
		
		uint32_t Quality_size_of_topic(const Quality* topic, uint32_t size)
		{
		    uint32_t previousSize = size;
		    size += ucdr_alignment(size, 1) + 1;
		
		    size += ucdr_alignment(size, 8) + 8;
		
		    size += ucdr_alignment(size, 4) + 4;
		
		    size += ucdr_alignment(size, 1) + 1;
		
		    size += ucdr_alignment(size, 1) + 1;
		
		    size += ucdr_alignment(size, 1) + 1;
		
		    size += ucdr_alignment(size, 1) + 1;
		
		    size += ucdr_alignment(size, 1) + 1;
		
		    return size - previousSize;
		}
 

        bool deserialize(const uint8_t *buffer, uint32_t length) override
        {
             
            ucdrBuffer ucdr_buffer;
            ucdr_init_buffer(&ucdr_buffer, buffer, length);
            return Quality_deserialize_topic(&ucdr_buffer, this);
             
        }

        long serialize(uint8_t *buffer, uint32_t max_size) override
        {
             
            ucdrBuffer ucdr_buffer;
            ucdr_init_buffer(&ucdr_buffer, buffer, max_size);
            bool ret = Quality_serialize_topic(&ucdr_buffer, this);
            if (!ret)
            {
                return -1;
            }
            else
            {
                return ucdr_buffer_length(&ucdr_buffer);
            }
             
        }

        virtual uint32_t maxSize() override
        {
             
            return Quality_size_of_topic(this, 0);
             
        }

    } quality_;
 
    struct Parameter : public FuncComponentBase
    {
 
		uint8_t frame_counter;
		uint64_t tai_seconds;
		uint32_t tai_nanoseconds;
		float drive_gear_ratio;
 
		bool Parameter_serialize_topic(ucdrBuffer* writer, const Parameter* topic)
		{
		    (void) ucdr_serialize_uint8_t(writer, topic->frame_counter);
		
		    (void) ucdr_serialize_uint64_t(writer, topic->tai_seconds);
		
		    (void) ucdr_serialize_uint32_t(writer, topic->tai_nanoseconds);
		
		    (void) ucdr_serialize_float(writer, topic->drive_gear_ratio);
		
		    return !writer->error;
		}
		
		bool Parameter_deserialize_topic(ucdrBuffer* reader, Parameter* topic)
		{
		    (void) ucdr_deserialize_uint8_t(reader, &topic->frame_counter);
		
		    (void) ucdr_deserialize_uint64_t(reader, &topic->tai_seconds);
		
		    (void) ucdr_deserialize_uint32_t(reader, &topic->tai_nanoseconds);
		
		    (void) ucdr_deserialize_float(reader, &topic->drive_gear_ratio);
		
		    return !reader->error;
		}
		
		uint32_t Parameter_size_of_topic(const Parameter* topic, uint32_t size)
		{
		    uint32_t previousSize = size;
		    size += ucdr_alignment(size, 1) + 1;
		
		    size += ucdr_alignment(size, 8) + 8;
		
		    size += ucdr_alignment(size, 4) + 4;
		
		    size += ucdr_alignment(size, 4) + 4;
		
		    return size - previousSize;
		}
 
        bool deserialize(const uint8_t *buffer, uint32_t length) override
        {
             
            ucdrBuffer ucdr_buffer;
            ucdr_init_buffer(&ucdr_buffer, buffer, length);
            return Parameter_deserialize_topic(&ucdr_buffer, this);
             
        }

        long serialize(uint8_t *buffer, uint32_t max_size) override
        {
             
            ucdrBuffer ucdr_buffer;
            ucdr_init_buffer(&ucdr_buffer, buffer, max_size);
            bool ret = Parameter_serialize_topic(&ucdr_buffer, this);

            if (!ret)
            {
                return -1;
            }
            else
            {
                return ucdr_buffer_length(&ucdr_buffer);
            }
             
        }

        virtual uint32_t maxSize() override
        {
             
            return Parameter_size_of_topic(this, 0);
             
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