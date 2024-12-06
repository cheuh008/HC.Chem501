# Database Structure and Example Data

## Introduction

This project stores experimental data in a SQLite database. The data is organized into three main tables: **experiments**, **metadata**, and **data**. Each table serves a specific role and is linked through `experiment_id` to associate the data across the tables. 

The database schema captures detailed information about various experiments, their metadata (e.g., substances used, environmental factors), and the recorded sensor data for each experiment.

## Database Schema

### **1. Experiments Table**

This table stores the details of each experiment conducted. The key fields are:

| Column           | Type    | Description                                      |
|------------------|---------|--------------------------------------------------|
| `experiment_id`  | TEXT    | A unique identifier for each experiment.         |
| `experiment_date`| TEXT    | The date when the experiment was conducted (YYYY-MM-DD). |

**Example Data**:
| experiment_id                                | experiment_date |
|----------------------------------------------|-----------------|
| 223a9f77-5fc1-4fff-bcf6-dffa702d2933         | 2024-11-27      |
| 3c6f211c-2746-4411-89fe-6672e198c3c1         | 2024-11-30      |
| a6b77242-1a8c-418a-a903-0cdd5420a54c         | 2024-11-27      |
| 2ddd68c0-972a-4273-be88-f70510ef3828         | 2024-11-28      |


### **2. Metadata Table**

This table stores metadata for each experiment, such as the substances used or environmental factors. The key fields are:

| Column            | Type    | Description                                          |
|-------------------|---------|------------------------------------------------------|
| `metadata_id`     | TEXT    | A unique identifier for each metadata entry.         |
| `experiment_id`   | TEXT    | The ID of the experiment to which this metadata belongs. |
| `metadata_type`   | TEXT    | The type of metadata (e.g., "Acetone", "Accuracy").   |
| `value`           | REAL    | The value of the metadata entry.                     |

**Example Data**:

| metadata_id                                  | experiment_id                                | metadata_type                     | value    |
|----------------------------------------------|----------------------------------------------|-----------------------------------|----------|
| fe900817-5076-43d8-9786-ff09ed3892de         | 223a9f77-5fc1-4fff-bcf6-dffa702d2933        c| Acetone                           | 0.0      |
| 876f0561-734b-4051-a7d2-3b12fdaa164f         | 223a9f77-5fc1-4fff-bcf6-dffa702d2933        c| Ambient                           | 100.0    |
| ...                                          | ...                                        c | ...                               | ...      |
| 73a5541b-fec3-4efa-9b36-7cc8face1710         | a6b77242-1a8c-418a-a903-0cdd5420a54c         | Gas Resistance (Ohms)             | 446673.0 |
| 8a21284d-2f06-4e80-bc8c-5ce40fb90c55         | a6b77242-1a8c-418a-a903-0cdd5420a54c         | Pressure (Pa)                     | 101807.14|
| ...                                          | ...                                        c | ...                               | ...      |

### **3. Data Table**

This table stores the actual experimental data recorded from the sensors for each experiment. The key fields are:

| Column            | Type    | Description                                         |
|-------------------|---------|-----------------------------------------------------|
| `data_id`         | TEXT    | A unique identifier for each data entry.            |
| `experiment_id`   | TEXT    | The ID of the experiment this data belongs to.      |
| `channel_name`    | TEXT    | The name of the data channel (e.g., "Acetone").     |
| `value`           | REAL    | The recorded value from the corresponding sensor.   |

**Example Data**:
| data_id                                     | experiment_id                                | channel_name                      | value   |
|---------------------------------------------|----------------------------------------------|-----------------------------------|---------|
| 63a23e4d-268d-4296-b0d6-b7d0956e80b3        | 223a9f77-5fc1-4fff-bcf6-dffa702d2933         | Acetone                           | 0.00    |
| 5097cfab-8363-419b-9701-bd561331eb6d        | 223a9f77-5fc1-4fff-bcf6-dffa702d2933         | Ambient                           | 100.00  |
| ...                                         | ...                                        c | ...                               | ...     |


## Relationships Between Tables

- The **experiments** table serves as the main table, with each experiment identified by a unique `experiment_id`.
- The **metadata** table contains various metadata about each experiment, where `experiment_id` is used to link it to the corresponding experiment in the **experiments** table.
- The **data** table stores the sensor data for each experiment. Each data entry includes an `experiment_id` and `channel_name`, linking it to the corresponding experiment and the type of data recorded.
